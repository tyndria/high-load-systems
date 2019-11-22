
# Trashcans

Let's try to create a **RESTful** (or sth near the REST) service.

## Service goal

The user wants to find the nearest trashcan with particular charactheristics
(whether it's possible to utilize glass or plastic).

If the trashcan doesn't exist on map, user should have a possibility to add it.

...
## REST 

We will use HTTP protocol, which will provide __*statelessness*__ princip of the REST architecture.

Since we are going to design basic api let's review __*uniform interface*__ princip more closely.

We will have the following resources:
- trashcan
- the list of the trashcans

We want to:
1. See the list of the nearest trashcans.
2. Add trashcan by its placement.
3. Modify trashcan properties. (TODO: what exactly?)

The resources will be identified using URIs.

### 1.Retrieve trashcans 

Since we use HTTP, to get the list of the nearest trashcans we will use *GET* request with the following URI:

`/trashcans?lat=53.904541&lng=27.561523&r=100`

### 2. Add trashcans

To add trashcan we will use *POST* method with the following URI:

`/trashcan`

### 3. Change trashcan's properties

To edit trashcan properties we'll use *PUT* method with the following URI:

`/trashcan/:id`

This is the way how we're going to __identify the resources in requests__.

To make API RESTful we should provide __self-descriptive messages__ princip.
Since this API looks like more public then private, we should think about sth more then just JSON representation.

For example, GeoJSON (https://tools.ietf.org/html/rfc7946)
