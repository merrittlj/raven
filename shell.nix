let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-25.05";
  nixpkgs-unstable = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-unstable";
  pkgs = import nixpkgs { config = { allowUnfree = true; }; overlays = []; };
  unstable = import nixpkgs-unstable { config = {}; overlays = []; };
  stm32cubeprog = pkgs.callPackage ./stm32cubeprog.nix {};
in
pkgs.mkShellNoCC {
  packages = with pkgs; [
    cmake
    ninja
    picocom
    doxygen
    newlib
    newlib-nano
    dfu-util
  ]++ [
    unstable.gcc-arm-embedded-13
    stm32cubeprog
  ]; # Stable gdb has deprecated python links
}
