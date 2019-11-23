
# Trashcans

Let's try to create a **RESTful** (or sth near the REST) service.

## Service goal

The user wants to *find the nearest trashcan* with particular charactheristics

If the trashcan doesn't exist on map, *user should have a possibility to add it*.
We also want to *see the charachteristics* of each trashcan and have the possibility to *edit it*.

...

## REST

We will use HTTP protocol, which will provide __*statelessness*__ princip of the REST architecture.

Since we are going to design basic api let's review __*uniform interface*__ princip more closely.

## Uniform interface 

We will have the following resources:
- trashcan
- the list of the trashcans

We want to:
1. See the list of the nearest trashcans and filter it.
2. Add trashcan by its placement.
3. Modify trashcan properties.

The resources will be identified using URIs.

### 1.Retrieve trashcans 

Since we use HTTP, to get the list of the nearest trashcans we will use *GET* request with the following URI:

`/trashcans?lat=53.904541&lng=27.561523&r=100`

It's also possible to filter trashcan by `type` parameter with the values `plastic|glass|paper`:

`/trashcans?lat=53.904541&lng=27.561523&r=100&type=plastic,paper`

### 2. Add trashcans

To add trashcan we will use *POST* method with the following URI:

`/trashcan`

### 3. Change trashcan's properties

To edit trashcan properties we'll use *PUT* method with the following URI:

`/trashcan/:id`

This is the way how we're going to __identify the resources in requests__.


What does trashcan look like inside?:)

Let's provide an example:

```
{
  latitude: number,
  longtitude: number,
  properties: {
    ...
  }
}
```


To make API RESTful we should provide __self-descriptive messages__ princip.
Since this API looks like more public then private, we should think about sth more then just JSON representation.

For example, GeoJSON (https://tools.ietf.org/html/rfc7946).
To add new trashcan to the map we will use approximately the following body:
```
{
    "type": "Feature",
    "geometry": {
        "type": "Point",
        "coordinates": [-104.99404, 39.75621]
    },
    "properties": {...}
}
```

List of the trashcans will look sth like this:
```
{
     "type": "FeatureCollection",
     "features": [{
         "type": "Feature",
         "geometry": {
             "type": "Point",
             "coordinates": [102.0, 0.5]
         },
         "properties": {...}
     }, {
         "type": "Feature",
         "geometry": {
             "type": "Point",
             "coordinates": [104.0, 0.5]
         },
         "properties": {...}
     }, ...]
}

```

A such representation of the data will help us to provide __self-descriptive messages__ princip of the REST architectural style.

But what about `Hypermedia as the engine of application state` princip?

According to it we don't want client to hard-code the information related to the structure of the application.
In our case when we're getting the list of the trashcans, I'd like to have an opportunity to edit some trashcan or see some characteristics of it. That's why it would be great to have hyperlink for each particular trashcan in the list.
According to the GeoJSON we could add this link as a field of `properties`. However, in this case we will lose __self-descriptive messages__ princip a bit. This is an example of __self-descriptive messages__ and __HATEOAS__ 
principles trade off.

In my opinion, our objects are geo-objects initialy, so I'd like to use **GeoJSON + link field in properties**.

The list of the trashcans will look sth like this:
```
{
     "type": "FeatureCollection",
     "features": [{
         "type": "Feature",
         "geometry": {
             "type": "Point",
             "coordinates": [102.0, 0.5]
         },
         "properties": {
             "link": "/trashcan/first"
         }
     }, {
         "type": "Feature",
         "geometry": {
             "type": "Point",
             "coordinates": [104.0, 0.5]
         },
         "properties": {
             "link": "/trashcan/second"
         }
     }, ...]
}

```
