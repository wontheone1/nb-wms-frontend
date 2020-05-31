module Ui = SemanticUi;
module M = Model;

[@react.component]
let make =
    (
      ~accountDetail: option(M.accountDetailType),
      ~dispatch,
      ~signedIn,
      ~signOut,
    ) =>
  <Ui.Menu secondary=true>
    <Ui.Menu.Item>
      {switch (accountDetail) {
       | Some({displayName, email}) =>
         React.string({j|$displayName($email)|j})
       | None => React.string({j|로그아웃 됨|j})
       }}
    </Ui.Menu.Item>
    <Ui.Menu.Menu position="right">
      <Ui.Menu.Item>
        <Ui.Input
          icon="search"
          onChange={event => {
            let value = ReactEvent.Form.target(event)##value;
            dispatch(M.SetSearchQuery(value));
          }}
          placeholder={j|검색...|j}
        />
      </Ui.Menu.Item>
      <Ui.Menu.Item>
        <Ui.Modal
          basic=true size="small" trigger={<Ui.Icon name="info circle" />}>
          <a
            href="https://fusejs.io/examples.html#extended-search"
            target="_blank">
            "https://fusejs.io/examples.html#extended-search"->React.string
          </a>
        </Ui.Modal>
      </Ui.Menu.Item>
      {signedIn
         ? <Ui.Menu.Item name="logout" onClick={_event => signOut()} />
         : <div />}
    </Ui.Menu.Menu>
  </Ui.Menu>;
