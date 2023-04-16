#pragma once

enum keys
{
  LOAD,
  SAVE,
  RUN,
  STEP,
  RESET,
  F5,
  F6,
  UP,
  DOWN,
  RIGHT,
  LEFT,
  ENTER,
  OTHER
};

int rk_readkey (enum keys *k);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);