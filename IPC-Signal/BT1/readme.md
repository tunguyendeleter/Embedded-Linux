# Bắt Tín Hiệu SIGINT

## 1. Mô tả
Chương trình này minh họa cách bắt tín hiệu SIGINT (gửi khi nhấn `Ctrl + C`) bằng cách sử dụng hàm `signal()`. Khi nhận được tín hiệu này, chương trình sẽ đếm số lần nhận và in ra thông báo tương ứng. Sau khi nhận đủ 3 lần tín hiệu SIGINT, chương trình sẽ kết thúc.

## 2. Yêu cầu
- Sử dụng hàm `signal()` để đăng ký một hàm xử lý tín hiệu SIGINT.
- Trong hàm xử lý, in ra thông báo "SIGINT received" kèm số lần nhận được tín hiệu.
- Chương trình tiếp tục chạy cho đến khi nhận được tín hiệu SIGINT lần thứ 3.

## 3. Giải thích Code
1. **Khai báo biến đếm:**
   ```c
   int sigint_count = 0;
   ```
   - Biến toàn cục `sigint_count` dùng để theo dõi số lần tín hiệu SIGINT được nhận.

2. **Hàm xử lý tín hiệu SIGINT:**
   ```c
   void SIGINT_handler(int num)
   {
       sigint_count++;
       printf("\n[INFO] SIGINT received: %d\n", sigint_count);
   }
   ```
   - Khi nhận được tín hiệu SIGINT, hàm này sẽ tăng biến `sigint_count` lên 1 và in ra thông báo số lần nhận được tín hiệu.

3. **Đăng ký hàm xử lý tín hiệu:**
   ```c
   if (signal(SIGINT, SIGINT_handler) < 0)
   {
       printf("\n[ERROR] Register signal fail");
       return 0;
   }
   ```
   - Hàm `signal(SIGINT, SIGINT_handler)` đăng ký `SIGINT_handler` làm hàm xử lý tín hiệu SIGINT.

4. **Vòng lặp chính:**
   ```c
   while (sigint_count < MAX_SIGINT)
   {
       /* Do nothing */
   }
   ```
   - Chương trình sẽ tiếp tục chạy cho đến khi `sigint_count` đạt giá trị 3, sau đó kết thúc.

## 4. Câu hỏi
### Nếu bỏ qua tín hiệu SIGINT, chuyện gì sẽ xảy ra khi nhấn Ctrl+C?
- Nếu không đăng ký xử lý tín hiệu SIGINT (tức là chương trình không sử dụng  `signal(SIGINT, SIG_IGN)`), khi nhấn `Ctrl + C`, hệ thống sẽ gửi tín hiệu SIGINT và tiến trình sẽ bị kết thúc ngay lập tức. Đây là hành vi mặc định của SIGINT.

## 5. Cấu trúc thư mục
```
.
├── bin
│   └── main
├── inc
├── lib
├── Makefile
├── obj
│   └── main.o
└── src
    └── main.c
```
- `src/main.c`: Chứa mã nguồn chính của chương trình.
- `bin/main`: Tệp thực thi sau khi biên dịch.
- `obj/main.o`: Tệp đối tượng sau khi biên dịch.
- `Makefile`: Tập lệnh biên dịch chương trình.
- `inc/` và `lib/`: Thư mục dành cho tệp tiêu đề và thư viện (nếu cần mở rộng).

## 6. Cách chạy chương trình
1. **Biên dịch chương trình** (giả sử có Makefile đi kèm):
   ```sh
   make
   ```
2. **Chạy chương trình:**
   ```sh
   ./bin/main
   ```
3. **Nhấn `Ctrl + C` ba lần để kết thúc chương trình.**

