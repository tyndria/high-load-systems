## What do we have

### 1. Retrieve *the nearest* trashcans.

This request is used by clients and I think that this is the most important and _usable_ request for clients,
so it's better to __quickly get the data__ rather than waiting for it a lot of time or repeat request.

__+1 for Availability__ + Partition tolerance

### 2. Add trashcan

Let's simplify the task. Let's imagine that trashcan could add only an employee of housing and communal services.
It means that we won't have any collisions and it will be easy to merge it.

Since the idea is to guarantee availability + partition tolerance we will have a problem:
if one person saves trashcan to one machine, another - to another machine,
users can catch the inconsistency of the data before synchronization while viewing the nearest trashcans.

_HERE IS THE ISSUE OF INCONSISTENCY_

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

When the users start to update the trashcan properties it can cause data discrepancy on different machines. 
The issue is _HOW TO MERGE DATA_ and _what to do if MACHINES LOST CONNECTION_? What we will show the users on get request?


##  What is better to do


So the service looks like Availability + Partition tolerance service.

### Cassandra 

__Cassandra isn't good at filtering__?

Let's look at Cassandra database.

#### Replication

It has the two main replication strategies are SimpleStrategy and NetworkTopologyStrategy.
Let's overview the first one.

It includes `replication_factor` defined the number of nodes that should contain a copy of each row.
Let's decide that we will have __`replication_factor = 3`__.

#### Consistency

Cassandra has _consistency levels_ specifying how many of the replicas need to respond in order to consider the operation a success (ONE, TWO, ALL and etc).

_Write operations are always sent to all replicas_, regardless of consistency level. 

Cassandra suggests using this formula `W + R > replication_factor`, where W is the write consistency level, R is the read consistency level.

> If QUORUM is used for both writes and reads, at least one of the replicas is guaranteed to participate in both the write and the read request,
> which in turn guarantees that the latest write will be read. 



