// Copyright 2019 Jack Khuu, Justin Johnson, Lukas Joswiak

#include "AMOStore.hpp"

#include <stdlib.h>

#include <map>
#include <string>
#include <iostream>

#include "Action.hpp"
#include "AMOCommand.hpp"
#include "AMOResponse.hpp"
#include "KVStore.hpp"

namespace KVStore {
using std::string;
using std::map;

AMOStore::AMOStore() : kv_store_(KVStore()) {}

bool AMOStore::AlreadyExecuted(const AMOCommand &command) const {
  return prev_.find(command) != prev_.end();
}

AMOResponse AMOStore::Execute(const AMOCommand &command) {
  string s;
  if (!AlreadyExecuted(command)) {
    switch (command.GetAction()) {
      case Action::kPut:
        s = kv_store_.Put(command.GetKey(), command.GetValue());
        break;
      case Action::kAppend:
        s = kv_store_.Append(command.GetKey(), command.GetValue());
        break;
      case Action::kGet:
        s = kv_store_.Get(command.GetKey());
        break;
      case Action::kKillServer:
      case Action::kReviveServer:
        s = "";
        break;
      default:
        std::cerr << "KVStore: unrecognized action: "
            << command.GetAction() << std::endl;
        exit(EXIT_FAILURE);
    }

    prev_[command] = AMOResponse(command, s);
  }

  return prev_[command];
}
}  // namespace KVStore
