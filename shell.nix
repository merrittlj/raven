let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-25.05";
  nixpkgs-unstable = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-unstable";
  pkgs = import nixpkgs { config = {}; overlays = []; };
  unstable = import nixpkgs-unstable { config = {}; overlays = []; };
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
  ]++ [ unstable.gcc-arm-embedded-13 ]; # Stable gdb has deprecated python links
}
