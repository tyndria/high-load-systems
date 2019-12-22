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

So we don't have problems with consistency here, but when sth goes wrong inside trashcan logic
which is responsible for tracking its state, we could __descrease the availability__,
since the trashcan is the only one that can do it.

So we could consider the second option.

- 3.2. Allow _users_ to update the trashcan state

When the users start to update the trashcan properties it can cause data discrepancy on different machines. 
The issue is _HOW TO MERGE DATA_ and _what to do if MACHINES LOST CONNECTION_? What we will show the users on get request?


#  What is better to do


So the service looks like Availability + Partition tolerance service.

## Amazon SimpleDB

__Partition__ could be done among _multiple domains_ to parallelize queries and
have them operate on smaller individual datasets.

It seems that it's a good option for us because we could use different domains for different areas/cities.
We don't need to complete requests from different domains and we could provide high availability since
data from the same domain will be replicated. 
In the unlikely event that one replica fails, Amazon SimpleDB can failover to another replica in the system.


DB supports two read consistency options: __eventually consistent read__ and consistent read.

Eventually consistency reads:
- stale reads possible;
- lowest read latency;
- highest read throughput.

Regarding the question of data conflict, when two users update the same entity (user_1_update, user_2_update) and then read,
SimpleDB says that the return result could be any: user_1_update, user_2_update or no results. It seems that we will have the same for the trashcan
post request.
But eventually consistency across all copies of the data is __usually__ reached within a second, so maybe it's not a big problem.

Amazon also suggests implementing some concurrent control mechanism, such as timestamp ordering, to ensure we are getting the data we want, so it seems that it will be the main factor while merging the data conflicts.