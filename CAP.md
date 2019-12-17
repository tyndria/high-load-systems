## What do we have

### 1. Retrieve *the nearest* trashcans.

This request is used by clients and I think that this is the most important and _usable_ request for clients,
so it's better to __quickly get the data__ even outdated rather than waiting for it a lot of time or repeat request.

__+1 for Availability__

### 2. Add trashcan

Let's simplify the task. Let's imagine that traschan could add only an employee of housing and communal services.
It means that we won't have any collisions and it will be easy to merge it.

So this request shouldn't violate consistency since it's not available for usual users.

__+1 for Availability__

### 3. Change trashcan's properties

Here we could simplify the situation as well.

In the API description we defines that trashcan has the following properties:

```
{
  plastic: boolean,
  glass: boolean,
  paper: boolean
}
```

Each of the true value property could mean that it's possible to utilize the trash of this type. 
If some of this is falsy it means that it's either full or unavailable at all.


We could imagine that this request is also called by an employee or the trashcan is tracking the state itself.
It means that we will have the only source of this request for particular trashcan. It means no conflicts
for particular trashcan. Moreover, update of one trashcan doesn't influence other trashcans.

So we don't have a problems with consistency here.

__+1 for Availability__






____________________


1. What guarantees do we want?

- What do we store?
We want to read only nearest traschans, we won't give all the list.

Each city is independant => no operations that influence several cities.

Each trashcan is independant. Modification of trashcan won't influence other traschcan properties =>
consistency at the level of trashcans (atomicity). => no need to store all trashcans toghether.


- How often do we want to "read"? How often do we want to "write"?

Writing is "traschcan" - the one source of truth. But if the traschcan is broken =>
repeating the request => alert that there is no connection with traschcan
We will write to one place, no conflicts on write?


Ok, what do we want to do with ONE TRASHCAN?

Consisteny (syncing) -> too long, timeout, but actual data
Availability is better then consistency because it will take time to reach the trashcan


Quick READ