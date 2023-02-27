#!/bin/bash

db=db.dat

set -e # abort the script if any command has errors

./database $db c 10 50

if ! [ $(ls -l $db | awk '{print $5}') -eq 1588 ]
then
  echo The size created by the database is not correct!
fi

if ! [ -z `./database $db l` ]
then
  echo "database wasn't empty! something is wrong"
fi

./database $db s 0 bob bob@bob.com 'I am bob. I am a builder'

if [ -z "`./database $db l`" ]
then
  echo "a user was added, but wasn't retrieved from $db"
fi

if [ -z "`./database $db g 0`" ]
then
  echo "get didn't work. uanble to retrive an added user"
fi


./database $db s 1 dave dave@fakewebsite.com 'I own a fake website'

if ! [ "$(./database $db l | wc -l)" -eq 2 ]
then
  echo Unable to add a second record
fi

if ! [ $(./database $db f zebra | wc -l) -eq 0 ]
then
  echo "search is returning results for a term that isn't in the database"
fi

if ! [ $(./database $db f bob | wc -l) -eq 1 ]
then
  echo "search isn't returning a result for a known record!"
fi

echo Finished running all tests!
