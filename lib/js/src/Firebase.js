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

export default function saveUser() {
  db.collection("users")
    .add({
      first: "Ada",
      last: "Lovelace",
      born: 1815,
    })
    .then(function (docRef) {
      console.log("Document written with ID: ", docRef.id);
    })
    .catch(function (error) {
      console.error("Error adding document: ", error);
    });
}
