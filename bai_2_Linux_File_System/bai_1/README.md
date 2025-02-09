Kết quả in ra sẽ in tại vị trí tiếp theo của file dữ liệu mà không bị đè lên dữ liệu của file trước đó bởi vì:
+ khi mở file với flag là O_APPEND con trỏ sẽ được đưa về cuối tệp
+ với lệnh ghi khi thực hiện ghi sẽ bắt đầu ghi vào cuối file mặc dù đã dùng lệnh fseek để đưa con trỏ về tệp
+ với lệnh đọc thì vẫn có thể đưa con trỏ về vị trí đầu file để tiến hành đọc dữ liệu