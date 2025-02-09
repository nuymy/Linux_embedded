
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 256

int main (void)
{
	int fd;
	int num_read, num_write;
	char buf_write_hello[12] = "Hello";
	char buf_write_thanh[12] = "Thanh";
	char buf_read[BUFFER_SIZE] ;

	//open file
	fd = open ("hello.txt", O_RDWR | O_CREAT | O_APPEND , 0667); // Khi mở tệp với cờ O_APPEND, mỗi lần thực hiện ghi (write), con trỏ tệp tự động được đặt ở cuối tệp. Điều này có nghĩa là nếu bạn không thay đổi vị trí con trỏ tệp bằng lseek, dữ liệu sẽ luôn được ghi vào cuối tệp.
	if (fd == -1){												//còn với thực hiện lệnh đọc, vẫn có thể sử dụng lênh lseek đưa con trỏ về đầu file và thực hiện việc đọc
        perror("Cannot open file\n");
        return -1;
    }	
	if (fd == -1){
		perror("Cannot read file\n");
		close (fd);
		return -1;
	}

	//write hello to file
	num_write = write(fd, buf_write_hello, strlen(buf_write_hello));
    if (num_write == -1) {
        perror("write file failed\n");
		close (fd);
		return -1;
    }

	//make file pointer to top file
	lseek(fd, 0, SEEK_SET);

	//read from file
	// num_read = read(fd, buf_read, BUFFER_SIZE -1);
	// if (num_read == -1) {
    //     perror("read file failed\n");
    //     close(fd);
    //     return -1;
    // }
	// // add null to buff
	// buf_read[num_read] = '\0';

	// In dữ liệu ra màn hình
	// printf("Nội dung tệp: %s\n", buf_read);

	// //write thanh to file
	num_write = write(fd, buf_write_thanh, strlen(buf_write_thanh));
    if (num_write == -1) {
        printf("write file failed\n");
		close(fd);
        return -1;
    }

	// //make file pointer to top file
	lseek(fd, 0, SEEK_SET);

	// ///read from file again
	num_read = read(fd, buf_read, BUFFER_SIZE -1);
	if (num_read == -1) {
        perror("read file failed\n");
        close(fd);
        return -1;
    }
	// // // add null to buff
	buf_read[num_read] = '\0';
	// printf data
	printf("Nội dung tệp: %s\n", buf_read);

    //close file
    close(fd);

    return 0;
}