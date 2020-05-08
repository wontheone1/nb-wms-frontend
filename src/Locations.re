[@react.component]
let make = (~signedIn) => {
  let initialLocations: array(Model.location) = [||];
  let (locations: array(Model.location), setLocations) =
    React.useState(() => initialLocations);

  React.useEffect1(
    () => {
      Firebase.readLocations(setLocations);
      None;
    },
    [|signedIn|],
  );

  signedIn
    ? Array.map(
        (loc: Model.location) => {
          <div> {React.string(loc.id ++ ": " ++ loc.desc)} </div>
        },
        locations,
      )
      ->React.array
    : <div />;
};
