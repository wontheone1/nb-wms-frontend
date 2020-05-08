[@bs.module "./Firebase.js"]
external createLocation: (string, string) => unit = "createLocation";

[@bs.module "./Firebase.js"] external readItems: unit => unit = "readItems";

[@bs.module "./Firebase.js"]
external readLocations:
  ((array(Model.location) => array(Model.location)) => unit) => unit =
  "readLocations";

[@bs.module "./FirebaseAuth.js"]
external mountSignInUI: unit => unit = "default";

[@bs.module "./FirebaseAuth.js"] external signOut: unit => unit = "signOut";
