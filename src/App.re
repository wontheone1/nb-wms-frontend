// This is the ReactJS documentation's useReducer example, directly ported over
// https://reactjs.org/docs/hooks-reference.html#usereducer

module Ui = SemanticUi;
module M = Model;

let rightButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="0px 4px 4px 0px", ~width="48px", ());
let sessionInfoStyle =
  ReactDOMRe.Style.make(
    ~borderRadius="0px 4px 4px 0px",
    ~width="48px",
    ~display="block",
    (),
  );

let hiddenDisplayStyle = ReactDOMRe.Style.make(~display="none", ());
let signinPlaceholder = ReactDOMRe.Style.make();

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
  let (accountDetail: option(M.accountDetailType), setAccountDetail) =
    React.useState(() => None);

  let signOut = () => {
    setSignedIn(_ => false);
    Firebase.signOut();
  };

  React.useEffect0(() => {
    Firebase.initApp(setSignedIn, setAccountDetail);
    None;
  });

  React.useEffect(() => {
    Firebase.mountSignInUI();
    None;
  });

  // We can use a fragment here, but we don't, because we want to style the counter
  <div>
    <Ui.Menu secondary=true>
      <Ui.Menu.Item>
        {switch (accountDetail) {
         | Some({displayName, email}) =>
           React.string({j|$displayName($email)|j})
         | None => React.string("Signed out")
         }}
      </Ui.Menu.Item>
      <Ui.Menu.Menu position="right">
        <Ui.Menu.Item>
          <Ui.Input icon="search" placeholder="Search..." />
        </Ui.Menu.Item>
        {signedIn
           ? <Ui.Menu.Item name="logout" onClick={_event => signOut()} />
           : <div />}
      </Ui.Menu.Menu>
    </Ui.Menu>
    <div
      style={signedIn ? hiddenDisplayStyle : signinPlaceholder}
      id="signin-placeholder"
    />
    {signedIn
       ? <div> <Locations signedIn /> <CreateLocationForm /> </div> : <div />}
  </div>;
};
