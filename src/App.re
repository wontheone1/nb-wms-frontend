// This is the ReactJS documentation's useReducer example, directly ported over
// https://reactjs.org/docs/hooks-reference.html#usereducer

let rightButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="0px 4px 4px 0px", ~width="48px", ());
let sessionInfoStyle =
  ReactDOMRe.Style.make(
    ~borderRadius="0px 4px 4px 0px",
    ~width="48px",
    ~display="block",
    (),
  );

// Record and variant need explicit declarations.
type state = {count: int};

type action =
  | Increment
  | Decrement;

let initialState = {count: 0};

let reducer = (state, action) => {
  switch (action) {
  | Increment => {count: state.count + 1}
  | Decrement => {count: state.count - 1}
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let (signedIn, setSignedIn) = React.useState(() => false);

  let signOut = () => {
    setSignedIn(_ => false);
    Firebase.signOut();
  };

  React.useEffect0(() => {
    Firebase.initApp(setSignedIn);
    None;
  });

  React.useEffect(() => {
    Firebase.mountSignInUI();
    None;
  });

  // We can use a fragment here, but we don't, because we want to style the counter
  <div>
    <div style=sessionInfoStyle>
      <div id="sign-in-status" />
      <div id="account-details" />
    </div>
    <Locations />
    <div style=sessionInfoStyle>
      {signedIn
         ? <button style=rightButtonStyle onClick={_event => signOut()}>
             {React.string("Sign out")}
           </button>
         : <p> {React.string("Signed out")} </p>}
      <CreateLocationForm />
    </div>
  </div>;
};
