# What do we have

## 1. Retrieve *the nearest* trashcans.

This request is used by clients and I think that this is the most important and _usable_ request for clients,
so it's better to __quickly get the data__ rather than waiting for it a lot of time.

__+1 for Availability__ + Partition tolerance

## 2. Add trashcan

Let's simplify the task. Let's imagine that trashcan could add only an employee of housing and communal services.
It means that we won't have any collisions and it will be easy to merge it.

If the idea is to guarantee availability + partition tolerance we will have a problem:
if one person saves trashcan to one machine, another - to another machine,
users can catch the inconsistency of the data before synchronization while viewing the nearest trashcans.

_HERE IS THE ISSUE OF INCONSISTENCY_

## 3. Change trashcan's properties

In the API description we define that trashcan has the following properties:

```
{
  plastic: boolean,
  glass: boolean,
  paper: boolean
}
```

Each of the true value could mean that it's possible to utilize the trash of this type. 
If some of this is falsy it means that it's either full or unavailable at all.

There are two possible  cases:

- 3.1. The request is called by _an employee or the trashcan_ is tracking the state itself

It means that we will have the only source of this request for a particular trashcan. It means no conflicts
for a particular trashcan. Moreover, an update of one trashcan doesn't influence other trashcans, 
it means that we have consistency at the level of trashcans.

But when sth goes wrong inside trashcan logic
which is responsible for tracking its state, we could __descrease the availability__,
since the trashcan is the only one that can do it.

So we could consider the second option.

- 3.2. Allow _users_ to update the trashcan state

When the users start to update the trashcan properties it can cause data discrepancy on different machines. 
The issue is _HOW TO MERGE DATA_ and _what to do if MACHINES LOST CONNECTION_? What we will show the users on get request?


#  What is better to do


So the service looks like Availability + Partition tolerance service.

## Amazon SimpleDB

__Partition__ will be done among _multiple domains_: in our case one domain in one city/area.

The main characteristics of domain:
- data inside the single domain is __replicated__ -> _availability_ for each domain;
- we aren't allowed to make cross-domain requests  -> that's ok, we don't need this;
- write is consistent for each domain.

In the unlikely event that one replica fails, SimpleDB can failover to another replica in the system.


DB supports two read consistency options: __eventually consistent__ read and __consistent__ read.

These are the statements from documentation:
> An eventually consistent read __might not reflect the results of a recently completed write__.
> Consistency across all copies of the data is usually _reached within a second_;

> A consistent read returns a result that reflects all writes that received a successful response prior to the read.


So let's review the cases of reading the data:

1. It seems that for __GET__ request of _particular trashcan_ we could use __consistent__ read to see a result that reflects all writes that received a successful response prior to the read. Because we'd like to make this request before changing the trashcan properties.

2. For the __GET__ request of _the list of trashcans_ we could use __eventually consistent__ read, since reaching the trashcan will take some
time anyway, so it's not essential to get the 100% actual data.


When the users _update the entity_ simultaneously we could use _optimistic concurrency control_ by maintaining a version number (or timestamp) attribute as part of an item and by performing a conditional update based on the value of this version number.
This mechanism is implemented using __conditional put__.


Retrieng _POST_ requests:
SimpleDB hs `itemName` field for the each item which should be unique. 
We can generate itemName value based on the coordinates / area identifier, so there couldn't be two trashcans inside one area or
with the same coordinates. It means that we won't be able to add two trashcans with the same coordinates / area identifier.

