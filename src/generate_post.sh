requests="PATCH||/hello_world/trashcan/trash_030.000000080.000000|||| {{\"properties\": {\"plastic\":true}}
GET||/hello_world/trashcans/lat/5/lng/5||
GET||/hello_world/trashcans/lat/5/lng/5||
GET||/hello_world/trashcans/lat/5/lng/5||
GET||/hello_world/trashcans/lat/5/lng/5||"

echo "$requests" | python make_ammo.py > ammo.txt