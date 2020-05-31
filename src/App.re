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

let initialState: M.state = {searchQuery: ""};

let reducer: (M.state, M.action) => M.state =
  (state, action) => {
    switch (action) {
    | M.SetSearchQuery(query) => {searchQuery: query}
    };
  };

let initialLocations: array(M.location) = [||];

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  let (signedIn, setSignedIn) = React.useState(() => false);
  let (accountDetail: option(M.accountDetailType), setAccountDetail) =
    React.useState(() => None);
  let (locations: array(M.location), setLocations) =
    React.useState(() => initialLocations);
  let panes: array(Ui.Tab.pane) = [|
    {
      menuItem: {j|위치관리|j},
      render: () =>
        <Ui.Tab.Pane attached=false>
          <Locations locations searchQuery={state.searchQuery} setLocations />
          <CreateLocationForm />
        </Ui.Tab.Pane>,
    },
    {
      menuItem: {j|재고관리|j},
      render: () =>
        <Ui.Tab.Pane attached=false>
          "not implemented"->React.string
        </Ui.Tab.Pane>,
    },
  |];

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
    <Ui.Header _as="h2">
      {j|NB 웨어하우스 메니지먼트 시스템에 오신 것을 환영합니다.|j}
      ->React.string
    </Ui.Header>
    <Menu accountDetail dispatch signedIn signOut />
    <SignInUiPlaceholder signedIn />
    {signedIn
       ? <Ui.Tab menu={secondary: true, pointing: true} panes /> : <div />}
  </div>;
};
