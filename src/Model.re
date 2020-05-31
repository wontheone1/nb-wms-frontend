type accountDetailType = {
  displayName: string,
  email: string,
};

type action =
  | SetSearchQuery(string);

type item = {
  articleId: string,
  location: string,
};

type article = {
  id: string,
  name: string,
};

type location = {
  id: string,
  desc: string,
};

type state = {searchQuery: string};
