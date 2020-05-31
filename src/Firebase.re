[@bs.module "./Firebase.js"]
external createOrEditLocation: (string, string) => unit =
  "createOrEditLocation";

[@bs.module "./Firebase.js"]
external deleteLocation: string => unit = "deleteLocation";

[@bs.module "./Firebase.js"] external readItems: unit => unit = "readItems";

[@bs.module "./Firebase.js"]
external readLocations:
  ((array(Model.location) => array(Model.location)) => unit) => unit =
  "readLocations";

[@bs.module "./FirebaseAuth.js"]
external mountSignInUI: unit => unit = "default";

[@bs.module "./FirebaseAuth.js"]
external initApp:
  (
    (bool => bool) => unit,
    (option(Model.accountDetailType) => option(Model.accountDetailType)) =>
    unit
  ) =>
  unit =
  "initApp";

[@bs.module "./FirebaseAuth.js"] external signOut: unit => unit = "signOut";
