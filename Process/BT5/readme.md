# Giới thiệu
Chương trình này minh họa cách tạo tiến trình Zombie và tiến trình Orphan trong hệ điều hành Linux. Chương trình tạo ra một cây tiến trình gồm "Grand Parent" (Ông), "Parent" (Cha), và hai tiến trình con.

# Yêu cầu
1. **Tiến trình Zombie:**
   - Một tiến trình con kết thúc nhưng tiến trình cha không gọi `wait()` để thu hoạch nó.
   - Quan sát tiến trình zombie bằng lệnh `ps`.

2. **Tiến trình Orphan:**
   - Một tiến trình cha kết thúc sớm trong khi tiến trình con vẫn còn chạy.
   - Tiến trình con sẽ trở thành tiến trình mồ côi và được `init` hoặc `systemd` tiếp quản.

# Cấu trúc chương trình
1. **Grand Parent (Tiến trình ông/bà):**
   - Tạo một tiến trình cha.
   - Chờ 3 giây rồi kiểm tra trạng thái các tiến trình con bằng `ps`.

2. **Parent (Tiến trình cha/mẹ):**
   - Tạo hai tiến trình con: `CHILD_1` và `CHILD_2`.
   - Tiến trình cha sẽ tự kết thúc, làm cho `CHILD_2` trở thành tiến trình mồ côi.
   - `CHILD_1` sẽ trở thành zombie vì cha nó kết thúc nhưng không wait() nó.

3. **CHILD_1 (Tiến trình zombie):**
   - Chạy vô hạn nhưng bị cha giết (`kill`), dẫn đến trạng thái zombie.

4. **CHILD_2 (Tiến trình orphan):**
   - Chạy vô hạn và trở thành orphan khi cha nó kết thúc.

# Cách chạy chương trình
1. **Biên dịch chương trình:**
   ```bash
   make
   ```
2. **Chạy chương trình:**
   ```bash
   ./bin/main
   ```
3. **Quan sát tiến trình zombie và orphan bằng lệnh:**
   ```bash
   ps -f
   ```

# Giải thích về tiến trình Zombie và Orphan
- **Zombie Process (Tiến trình ma):**
  - Khi một tiến trình con kết thúc nhưng cha nó không gọi `wait()`, tiến trình con sẽ vẫn còn trong bảng tiến trình của hệ thống với trạng thái `Z` (zombie).
  - Tiến trình zombie tồn tại cho đến khi cha nó đọc mã thoát bằng `wait()` hoặc cha nó cũng bị kết thúc.

- **Orphan Process (Tiến trình mồ côi):**
  - Khi một tiến trình cha kết thúc trước tiến trình con, tiến trình con sẽ trở thành orphan.
  - Tiến trình orphan sẽ được hệ thống tự động chuyển giao cho tiến trình `init` hoặc `systemd`, đảm bảo nó không trở thành zombie.

# Kết luận
Chương trình giúp hiểu cách hệ điều hành Linux quản lý các tiến trình đặc biệt như Zombie và Orphan. Đây là những khái niệm quan trọng trong quản lý tiến trình và hệ điều hành.

