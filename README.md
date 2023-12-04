# CUB3D

## DOWNLOAD

```bash
git clone --recurse-submodules https://github.com/Elnop/42-cub3d.git 42-lperroti-cub3d
cd ./42-lperroti-cub3d
make
```
## START
 
```bash
./cub3d
```
## SRCS

- [Doc Raycasting](https://lodev.org/cgtutor/raycasting.html)

## VALGRIND

show program problems with [valgrind](https://valgrind.org/)

flags for cud3d

- --track-fds : track open file descriptors
- --leak-check : search for memory leaks at exit

```bash
valgrind --track-fds=yes --leak-check=full ./cub3d

```