{ 
  pkgs ? import <nixpkgs> {}
}:

with pkgs;

pkgs.stdenv.mkDerivation (finalAttrs: {
  pname = "touch-scroll-physics-c";
  version = "0.0.1";

  src = ./.;

  outputs = [ "out" ];
  nativeBuildInputs = [ cmake ninja ];
  enableParallelBuilding = true;

  configurePhase = ''
    cmake . -G Ninja -DCMAKE_INSTALL_PREFIX=$out
  '';

  meta = with lib; {
    description = "Quick port of a JavaScript scroll library to C.";
    homepage = "https://github.com/bramtechs/touch-scroll-physics-c";
    license = licenses.mit;
    maintainers = with maintainers; [ brambasiel ];
    platforms = platforms.all;
    changelog = "https://github.com/bramtechs/touch-scroll-physics-c";
  };
})
