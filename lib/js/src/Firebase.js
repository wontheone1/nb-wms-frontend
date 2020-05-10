const firebase = require("firebase");
// Required for side-effects
require("firebase/firestore");

// Your web app's Firebase configuration
var firebaseConfig = {
  apiKey: "AIzaSyDgc8_50X0s3WSUw0ksI5iPggqDr7Nehx0",
  authDomain: "nb-wms.firebaseapp.com",
  databaseURL: "https://nb-wms.firebaseio.com",
  projectId: "nb-wms",
  storageBucket: "nb-wms.appspot.com",
  messagingSenderId: "246548713087",
  appId: "1:246548713087:web:96024266427c644b17f94a",
  measurementId: "G-KTVDWZ9KJJ",
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);
firebase.analytics();

var db = firebase.firestore();

export function createLocation(id, desc) {
  db.collection("locations")
    .doc(id)
    .set({
      desc: desc,
    })
    .then(function (docRef) {
      console.log("Doc created/updated:");
      console.log(docRef);
    })
    .catch(function (error) {
      console.error("Error adding document: ", error);
    });
}

export function readLocations(setLocations) {
  db.collection("locations")
    .get()
    .then((querySnapshot) => {
      querySnapshot.forEach((doc) => {
        console.log(`ID: ${doc.id}`);
        console.log(doc.data());
        setLocations((currentLocations) => [
          ...currentLocations,
          { id: doc.id, desc: doc.data().desc },
        ]);
      });
    });
}

export function readItems() {
  db.collection("items")
    .get()
    .then((querySnapshot) => {
      querySnapshot.forEach((doc) => {
        console.log(`${doc.id}`);
        console.log(`barcode: ${doc.data().barcode}`);
        console.log(`location_barcode: ${doc.data().location_barcode}`);
      });
      //     return querySnapshot;
    });
}
