
# Trashcans

Let's try to create __sth near the RESTful__ service.

## Service goal

The user wants to *find the nearest trashcan* with particular characteristics

If the trashcan doesn't exist on a map, *user should have a possibility to add it*.
We also want to *see the characteristics* of each trashcan and have the possibility to *edit it*.

## REST

We will use the HTTP protocol, which will provide __*statelessness*__ principle of the REST architecture.

Since we are going to design basic API let's review __*uniform interface*__ principle more closely. All other principals like client-server architecture, cacheability, layered system will be covered in the next laboratories.

## Uniform interface 

We will have the following resources:
- trashcan
- the list of the trashcans

We want to:
1. See the list of the nearest trashcans and filter it.
2. Add trashcan by its placement with properties.
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
    plastic: boolean,
    glass: boolean,
    paper: boolean
  }
}
```


To make API RESTful we should provide __self-descriptive messages__ principle.
Since this API looks more public than private, we should think about sth more than just JSON representation.

For example, GeoJSON (https://tools.ietf.org/html/rfc7946).
__To add new trashcan__ to the map we will use approximately the following body:
```
{
  "type": "Feature",
  "geometry": {
    "type": "Point",
    "coordinates": "[-104.99404, 39.75621]"
  },
  "properties": {
    "plastic": "true",
    "paper": "false",
    "glass": "false"
  }
}
```

__Response__ will look in this way:
```
{
  "type": "Feature",
  "geometry": {
    "type": "Point",
    "coordinates": "[-104.99404, 39.75621]"
  },
  "properties": {
    "plastic: "true",
    "paper": "false",
    "glass": "false",
    "_links": {
      "self": {
        "href": "/trashcan/first"
      }
    }
  }
}
```


__List of the trashcans__ will look sth like this:
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

Such representation of the data will help us to provide __self-descriptive messages__ principle of the REST architectural style.

But what about `Hypermedia as the engine of application state` principle?

According to it, we don't want the client to hard-code the information related to the structure of the application.
In our case when we're getting the list of the trashcans, I'd like to have an opportunity to edit some trashcan or see some characteristics of it. That's why it would be great to have a hyperlink for each particular trashcan on the list.

Firstly we could think about using `home document` to help the client avoid resource identifiers hardcoding.
This entry point could look approximately in this way:

```
{
  "resources": {
    "http://cool-minsk/trashcans": {
      "href": "/trashcans/"
    },
    "http://cool-minsk/trashcans": {
      "href-template": "/trashcans?lat={lat}&lng={lng}&r={r}",
      "href-vars": {
        "lat": "http://cool-minsk/param/lat/trashcans",
        "lng": "http://cool-minsk/param/lng/trashcans",
        "lr": "http://cool-minsk/param/r/trashcans",
      },
    },
    "http://cool-minsk/trashcan": {
      "href-template": "/trashcan/{trashcan_id}",
      "href-vars": {
        "trashcan_id":  "http://cool-minsk/param/trashcan",
      },
    }
  }
}
```

Such an approach allows a server to add new features, control resources clients are using, choose what URLs to use for a given service.

According to the GeoJSON, we could add this link as a field of `properties`. However, in this case, we will lose __self-descriptive messages__ principle a bit. This is an example of __self-descriptive messages__ and __HATEOAS__ 
principles trade-off.

In my opinion, our objects are geo-objects initially, so I'd like to use **GeoJSON + HAL in properties**.

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
      "_links": {
        "self": {
          "href": "/trashcan/first"
        }
      }
    }
  }, {
    "type": "Feature",
    "geometry": {
      "type": "Point",
      "coordinates": [104.0, 0.5]
    },
    "properties": {
      "_links": {
        "self": {
          "href": "/trashcan/second"
        }
      }
    }
  }, ...]
}

```

# Summary

For now, we assume that we don't have problems with __*statelessness, client-server architecture, cacheability, layered system*__ principals while implementing RESTful API.

However, we've noticed  __self-descriptive messages__ and __HATEOAS__ principles trade-off, since GeoJSON doesn't have a fixed property for the trashcan link. It means that's for now out API is close but no the classic REST.