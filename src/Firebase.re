[@bs.module "./Firebase.js"] external saveUser: unit => unit = "default";
[@bs.module "./Firebase.js"] external readItems: unit => unit = "readItems";
[@bs.module "./FirebaseAuth.js"]
external mountSignInUI: unit => unit = "default";
[@bs.module "./FirebaseAuth.js"] external signOut: unit => unit = "signOut";
