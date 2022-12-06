{ pkgs }: {
	deps = [
		pkgs.nano
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
		pkgs.cmake
		pkgs.boost
	];
}
