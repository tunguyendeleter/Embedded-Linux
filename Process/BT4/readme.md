# Chương trình tạo tiến trình con và chờ tiến trình con kết thúc

## 1. Mô tả chương trình
Chương trình này tạo hai tiến trình con bằng cách sử dụng hàm `fork()`. Sau khi tiến trình con kết thúc, tiến trình cha sử dụng `wait()` để chờ tiến trình con kết thúc và thu nhận trạng thái thoát của nó.

## 2. Yêu cầu
- Tiến trình cha tạo hai tiến trình con.
- Mỗi tiến trình con thực hiện một công việc đơn giản và kết thúc bằng `exit()`, truyền một mã trạng thái cụ thể.
- Tiến trình cha sử dụng `wait()` để chờ từng tiến trình con kết thúc.
- Sau khi một tiến trình con kết thúc, tiến trình cha thu nhận mã trạng thái thoát bằng cách sử dụng `WIFEXITED()` và `WEXITSTATUS()` để kiểm tra xem tiến trình con có kết thúc bình thường không và mã trạng thái mà nó trả về.

## 3. Giải thích các phần quan trọng trong chương trình
### 3.1. Tạo tiến trình con
```c
pid_t child1, child2;
child1 = fork();
```
- `fork()` tạo một tiến trình con. Nếu thành công, tiến trình con sẽ chạy song song với tiến trình cha.
- Nếu `fork()` trả về `0`, đây là tiến trình con.
- Nếu `fork()` trả về giá trị dương, đây là tiến trình cha và giá trị trả về là PID của tiến trình con.
- Nếu `fork()` trả về giá trị âm, tức là tạo tiến trình con thất bại.

### 3.2. Tiến trình con kết thúc với một mã trạng thái
```c
if (child1 == 0) {
    printf("[CHILD 1] I'm the child, my PID = %d\n", getpid());
    sleep(1);  // Ngủ để tránh tiến trình zombie
    exit(111); // Thoát với mã trạng thái 111
}
```
- Tiến trình con sau khi được tạo sẽ in ra PID của nó và thoát bằng `exit(111)`, truyền mã trạng thái `111` về tiến trình cha.

### 3.3. Tiến trình cha sử dụng wait() để thu nhận trạng thái kết thúc
```c
pid_t pid1, pid2;
int status1, status2;

pid1 = wait(&status1);
printf("[PARENT] PID child1 = %d\n", pid1);
printf("[PARENT] WIFEXITED(child1) = %d, WEXITSTATUS(child1) = %d\n", WIFEXITED(status1), WEXITSTATUS(status1));
```
- `wait(&status1)` giúp tiến trình cha chờ tiến trình con kết thúc.
- `WIFEXITED(status1)` kiểm tra xem tiến trình con có kết thúc bình thường không.
- `WEXITSTATUS(status1)` lấy mã trạng thái mà tiến trình con truyền về khi thoát.

### 3.4. Chương trình tránh tiến trình zombie
- Nếu tiến trình cha không gọi `wait()`, tiến trình con sau khi kết thúc sẽ ở trạng thái **zombie**.
- Khi tiến trình cha gọi `wait()`, hệ điều hành sẽ giải phóng tài nguyên của tiến trình con.

## 4. Kết quả mong đợi
Sau khi chạy chương trình, kết quả có thể như sau:
```
[CHILD 1] I'm the child, my PID = 1234
[CHILD 2] I'm the child, my PID = 1235
[PARENT] I'm the parent, my PID = 1233
[PARENT] Receive child1's status:
[PARENT] PID child1 = 1234
[PARENT] WIFEXITED(child1) = 1, WEXITSTATUS(child1) = 111
[PARENT] Receive child2's status:
[PARENT] PID child2 = 1235
[PARENT] WIFEXITED(child2) = 1, WEXITSTATUS(child2) = 222
```

## 5. Câu hỏi
1. **Tại sao cần sử dụng `wait()` trong tiến trình cha?**
   - `wait()` giúp tiến trình cha thu nhận trạng thái thoát của tiến trình con và ngăn chặn tiến trình con trở thành **zombie**.

2. **Sự khác biệt giữa `WIFEXITED()` và `WEXITSTATUS()` là gì?**
   - `WIFEXITED(status)` kiểm tra xem tiến trình con có kết thúc bình thường không.
   - `WEXITSTATUS(status)` lấy mã trạng thái mà tiến trình con đã truyền về.

3. **Điều gì xảy ra nếu tiến trình cha không gọi `wait()`?**
   - Nếu tiến trình cha không gọi `wait()`, tiến trình con sẽ chuyển sang trạng thái **zombie**, chiếm tài nguyên hệ thống mà không được giải phóng.

## 6. Kết luận
Chương trình này minh họa cách tiến trình cha sử dụng `fork()` để tạo tiến trình con và `wait()` để thu nhận trạng thái thoát của tiến trình con, đảm bảo rằng không có tiến trình zombie tồn tại sau khi tiến trình con kết thúc.

