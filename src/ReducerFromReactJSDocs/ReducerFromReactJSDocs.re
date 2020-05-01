// This is the ReactJS documentation's useReducer example, directly ported over
// https://reactjs.org/docs/hooks-reference.html#usereducer

// A little extra we've put, because the ReactJS example has no styling
let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());
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

[@bs.module "../Firebase.js"] external saveUser: unit => unit = "default";
[@bs.module "../Firebase.js"] external readItems: unit => unit = "readItems";
[@bs.module "../FirebaseAuth.js"]
external mountSignInUI: unit => unit = "default";
[@bs.module "../FirebaseAuth.js"] external signOut: unit => unit = "signOut";

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  React.useEffect(() => {
    mountSignInUI();
    readItems();
    None;
  });

  // We can use a fragment here, but we don't, because we want to style the counter
  <div>
    <div style=sessionInfoStyle>
      <div id="sign-in-status" />
      <div id="account-details" />
    </div>
    <div style=sessionInfoStyle>
      <button style=leftButtonStyle onClick={_event => signOut()}>
        {React.string("Sign out")}
      </button>
      <button style=leftButtonStyle onClick={_event => saveUser()}>
        {React.string("-")}
      </button>
    </div>
  </div>;
};
