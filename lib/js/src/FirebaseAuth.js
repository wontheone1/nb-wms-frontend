var firebase = require("firebase");
var firebaseui = require("firebaseui");

// FirebaseUI config.
var uiConfig = {
  signInSuccessUrl: "<url-to-redirect-to-on-success>",
  signInOptions: [
    // Leave the lines as is for the providers you want to offer your users.
    firebase.auth.GoogleAuthProvider.PROVIDER_ID,
  ],
  // tosUrl and privacyPolicyUrl accept either url string or a callback
  // function.
  // Terms of service url/callback.
  tosUrl: function () {
    window.alert("dummy Terms of service");
  },
  // Privacy policy url/callback.
  privacyPolicyUrl: function () {
    window.alert("dummy privacy policy");
  },
};

// Initialize the FirebaseUI Widget using Firebase.
var ui = new firebaseui.auth.AuthUI(firebase.auth());
// The start method will wait until the DOM is loaded.
export default function () {
  ui.start("#signin_placeholder", uiConfig);
}
