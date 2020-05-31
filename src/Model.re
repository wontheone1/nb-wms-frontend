type accountDetailType = {
  displayName: string,
  email: string,
};

type action =
  | SetSearchQuery(string);

type location = {
  id: string,
  desc: string,
};

type state = {searchQuery: string};
