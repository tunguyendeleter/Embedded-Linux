# Sử dụng exec và Biến Môi Trường

## Mô tả
Chương trình này minh hoạ cách sử dụng hàm `exec` trong lập trình C để thay thế tiến trình hiện tại bằng một chương trình khác.

Tiến trình con được tạo và thay thế chính nó bằng việc chạy các lệnh như `ls` hoặc `date` tùy thuộc vào đối số truyền vào.

## Cách chạy chương trình
1. Biên dịch chương trình bằng `make`:
   ```sh
   make
   ```
2. Chạy chương trình với tham số truyền vào:
   - Chạy lệnh `ls`:
     ```sh
     ./bin/main 1
     ```
   - Chạy lệnh `date`:
     ```sh
     ./bin/main 2
     ```

## Câu hỏi và Giải thích
1. **Chế độ hoạt động của exec trong chương trình?**
   - Khi hàm `exec` được gọi, nó thay thế hoàn toàn tiến trình hiện tại bằng chương trình được chỉ định.
   - Toàn bộ bộ nhớ, mã lệnh, biến môi trường của tiến trình ban đầu bị ghi đè bởi chương trình mới.

2. **Tiến trình gốc xảy ra điều gì sau khi exec được gọi?**
   - Tiến trình ban đầu bị thay thế hoàn toàn, nên các dòng code sau lệnh `exec` sẽ không bao giờ được thực thi.
   - Nếu `exec` thất bại (chương trình chỉ định không tồn tại), tiến trình sẽ tiếp tục chạy từ dòng code sau `exec`.

## Cây thư mục
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

## Ghi chú
- `bin/`: Chứa file thực thi.
- `obj/`: Chứa file object tạm.
- `src/`: Chứa mã nguồn C.
- `Makefile`: Quản lý quá trình biên dịch.

