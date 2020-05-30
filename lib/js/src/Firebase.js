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

export function deleteLocation(id) {
  db.collection("locations")
    .doc(id)
    .delete()
    .then(function () {
      console.log("Document successfully deleted!");
    })
    .catch(function (error) {
      console.error("Error removing document: ", id, error);
    });
}

export function readLocations(setLocations) {
  setLocations((_) => []);
  db.collection("locations").onSnapshot((querySnapshot) => {
    querySnapshot.docChanges().forEach((change) => {
      if (change.type === "added") {
        console.log("Added: ", change.doc.id, change.doc.data());
        setLocations((currentLocations) => [
          ...currentLocations,
          { id: change.doc.id, desc: change.doc.data().desc },
        ]);
      }

      // if (change.type === "modified") {
      //   console.log("Modified city: ", change.doc.data());
      // }

      if (change.type === "removed") {
        console.log("Removed: ", change.doc.id);
        setLocations((currentLocations) => {
          return currentLocations.filter((loc) => loc.id != change.doc.id);
        });
      }
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
