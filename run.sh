#!/bin/bash

USER_LOGIN="u467160"
USER_PASSWORD="55d9fe6c-da4a-4f5a-94a2-cdec8c4e69c1"

mono ./RemoteTasks/Portable.RemoteTasks.Manager.exe \
  -ul "$USER_LOGIN" \
  -up "$USER_PASSWORD" \
   "$@"
