{ pkgs ? import <nixpkgs> {}, doom ? import <doomhowl> {} }:

with pkgs;

mkShell
  {
    stdenv = pkgs.llvmPackages_18.libcxxStdenv;

    buildInputs = [
      doom.raylib
      llvmPackages_18.clangUseLLVM
    ];
  }
