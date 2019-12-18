## What do we have

### 1. Retrieve *the nearest* trashcans.

This request is used by clients and I think that this is the most important and _usable_ request for clients,
so it's better to __quickly get the data__ even outdated rather than waiting for it a lot of time or repeat request.

__+1 for Availability__

### 2. Add trashcan

Let's simplify the task. Let's imagine that trashcan could add only an employee of housing and communal services.
It means that we won't have any collisions and it will be easy to merge it.

So this request shouldn't violate consistency since it's not available for usual users.

__+1 for Availability__

### 3. Change trashcan's properties

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

Since we won't have to update trashcan on different machines, we won't have problems with consistency here.
But the user will always have an "almost actual" state of the trashcan.
We also don't have problems with consistency from ACID perspective, since the properties of the trashcan could be either true or false, we can't get negative value or sth like this.

I prefer to choose the second option.

##  What is better to do

Let's divide the trashcans by districts/cities. The one machine will simply store the trashcans of a particular city/district.

Each of those machines should have replication to guarantee availability.

Data between replication will be synchronized in the background (is this a place of inconsistency (or eventual consistency)?).