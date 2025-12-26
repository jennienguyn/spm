# SAMP Proof Manager

**SAMP Proof Manager** là một ứng dụng nhỏ chạy trên Windows, được viết bằng **C (WinAPI)**, dùng để giúp người chơi **SA-MP Roleplay** quản lý các video bằng chứng ghi lại trong quá trình chơi (ví dụ bằng Bandicam hoặc OBS).

Ứng dụng chạy nền, không can thiệp vào game, mục tiêu chính là giúp việc lưu trữ và tìm lại video trở nên dễ dàng hơn khi cần report hoặc kháng cáo.

---

## Trạng thái dự án

**Alpha**

Dự án hiện vẫn đang ở giai đoạn alpha.
Các chức năng chính đã hoạt động, tuy nhiên vẫn có thể tồn tại lỗi, hành vi chưa ổn định hoặc những điểm chưa được hoàn thiện về giao diện và trải nghiệm sử dụng.

---

## Chức năng hiện có

* Chọn thư mục lưu video
* Tự động đổi tên video ngay khi file mới được tạo
* Hỗ trợ định dạng tên file tuỳ chỉnh theo ngày giờ và username
* Tự động xoá video cũ sau số ngày cấu hình
* Tuỳ chọn tự khởi động cùng Windows
* Chạy nền, không ảnh hưởng đến hiệu năng game

---

## Công nghệ sử dụng

* Ngôn ngữ: **C**
* Giao diện: **WinAPI**
* Theo dõi file: `ReadDirectoryChangesW`
* Build: **MinGW (GCC)**
* Nền tảng: **Windows**

---

## Build

```bash
gcc main.c gui.c watcher.c utils.c config.c autostart.c ^
-mwindows -o SAMPProofManager.exe
```

---

## Ghi chú

* Ứng dụng không phải cheat và không đọc hay can thiệp vào dữ liệu game
* Video bằng chứng nên được giữ nguyên, không chỉnh sửa
* Dự án được xây dựng cho mục đích cá nhân và học tập