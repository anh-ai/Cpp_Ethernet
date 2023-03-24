# Cpp_Ethernet
- [C++ - JSON - Ethernet](https://github.com/anh-ai/Cpp_Ethernet/edit/main/README.md#c---json---ethernet)
- [C++ - Array - Ethernet](https://github.com/anh-ai/Cpp_Ethernet/edit/main/README.md#c---array---ethernet)
- [Ví dụ mã nguồn cho phía máy chủ như sau:](https://github.com/anh-ai/Cpp_Ethernet/edit/main/README.md#v%C3%AD-d%E1%BB%A5-m%C3%A3-ngu%E1%BB%93n-cho-ph%C3%ADa-m%C3%A1y-ch%E1%BB%A7-nh%C6%B0-sau)


## C++ - JSON - Ethernet

Gửi thông tin sau:

`mess={ "id":33, "test":1, "box": 0, "SN":"sn012345678901234567890" }`

dùng ethernet socket đến server.
Đây là một ví dụ về cách gửi dữ liệu JSON qua ổ cắm Ethernet bằng C++:

c++

```c
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <jsoncpp/json/json.h>

int main() {
    // Create a JSON object
    Json::Value mess;
    mess["id"] = 33;
    mess["test"] = 1;
    mess["box"] = 0;
    mess["SN"] = "sn012345678901234567890";

    // Convert the JSON object to a string
    std::string json_str = Json::FastWriter().write(mess);

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Set up the server address and port
    struct sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("SERVER_IP_ADDRESS");
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    // Send the JSON data over the socket
    if (send(sock, json_str.c_str(), json_str.size(), 0) < 0) {
        std::cerr << "Error sending data" << std::endl;
        return 1;
    }

    // Close the socket
    close(sock);

    return 0;
}
```

Replace `SERVER_IP_ADDRESS` and `SERVER_PORT` with the IP address and port number of the server you want to send the JSON data to. Also, make sure to include the JSONCPP library in your project.



Trong ví dụ mã nguồn C++ mà tôi cung cấp trước đó, tôi đã sử dụng các thư viện C++ sau đây:

*   `<iostream>`: thư viện dòng vào/ra chuẩn để nhập và xuất dữ liệu trên console.
*   `<cstring>`: thư viện xử lý chuỗi.
*   `<sys/socket.h>`: thư viện mạng cấp thấp để lập trình socket.
*   `<arpa/inet.h>`: tệp tiêu đề định nghĩa các hàm để xử lý địa chỉ IP.
*   `<unistd.h>`: tệp tiêu đề định nghĩa hằng số và kiểu ký hiệu khác, và khai báo các hàm khác nhau.
*   `<jsoncpp/json/json.h>`: tệp tiêu đề cho thư viện JSONCPP cung cấp các hàm để phân tích cú pháp và tạo ra dữ liệu JSON.

Năm thư viện đầu tiên thường được bao gồm theo mặc định trong hầu hết các trình biên dịch C++ cho Windows. Tuy nhiên, đối với thư viện JSONCPP, bạn cần cài đặt nó trước khi sử dụng nó trong dự án của bạn. Dưới đây là cách cài đặt thư viện trên Windows:

1.  Tải mã nguồn thư viện JSONCPP từ kho lưu trữ GitHub chính thức: [https://github.com/open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp)
    
2.  Giải nén tệp ZIP tải xuống vào một thư mục tùy chọn.
    
3.  Mở Command Prompt hoặc PowerShell và điều hướng đến thư mục bạn giải nén mã nguồn JSONCPP.
    
4.  Chạy các lệnh sau để xây dựng và cài đặt thư viện:
    

bash

```bash
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF -DJSONCPP_WITH_WARNING_AS_ERROR=OFF ..
cmake --build . --config Release
cmake --install .
```

Các lệnh trên sẽ tạo một dự án Visual Studio, xây dựng thư viện ở chế độ Release và cài đặt nó vào vị trí mặc định trên hệ thống của bạn.

5.  Sau khi cài đặt hoàn tất, bạn có thể bao gồm tệp tiêu đề JSONCPP vào mã C++ của mình bằng cách thêm dòng sau ở đầu tệp:

c++

```c
#include <jsoncpp/json/json.h>
```

 Bây giờ bạn có thể sử dụng thư viện JSONCPP trong dự án C++ trên Windows.

## C++ - Array - Ethernet 
Thay vì dùng json, chúng ta gửi một array có thông tin tương tự lên ethernet:

Để gửi một mảng chứa thông tin tương tự lên Ethernet, ta có thể sử dụng một cấu trúc dữ liệu đại diện cho thông tin đó, sau đó đóng gói các thành phần của cấu trúc dữ liệu vào một mảng byte và gửi mảng byte đó qua Ethernet. Trong ví dụ này, ta sẽ sử dụng một cấu trúc dữ liệu đại diện cho thông tin như sau:

c++

```c
struct MyData {
    int id;
    int test;
    int box;
    char sn[21];
};
```

Cấu trúc dữ liệu này có thể lưu trữ thông tin giống như ví dụ trước đó về đối tượng JSON mà không cần sử dụng thư viện phân tích cú pháp JSON. Sau đó, ta đóng gói các thành phần của cấu trúc dữ liệu vào một mảng byte và gửi mảng byte đó qua Ethernet. Bạn có thể sử dụng hàm `memcpy` để sao chép dữ liệu vào mảng byte và hàm `send` để gửi mảng byte đó qua Ethernet. Ví dụ mã nguồn cho việc đóng gói và gửi một mảng byte chứa dữ liệu của cấu trúc `MyData`:

c++

```c
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

struct MyData {
    int id;
    int test;
    int box;
    char sn[21];
};

int main() {
    // tạo socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // thiết lập địa chỉ và cổng của máy chủ
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.100");

    // kết nối đến máy chủ
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }

    // tạo cấu trúc dữ liệu MyData
    MyData data;
    data.id = 33;
    data.test = 1;
    data.box = 0;
    strcpy(data.sn, "sn012345678901234567890");

    // đóng gói dữ liệu vào một mảng byte
    char buffer[sizeof(MyData)];
    memcpy(buffer, &data, sizeof(MyData));

    // gửi mảng byte qua Ethernet
    if (send(sockfd, buffer, sizeof(buffer), 0) < 0) {
        perror("send failed");
        exit(EXIT_FAILURE);
    }

    // đóng kết nối
    close(sockfd);

    return 0;
}
```

Trong ví dụ này, ta đã tạo một cấu trúc dữ liệu `MyData` để lưu trữ thông tin, bao gồm các trường `id`, `test`, `box` và `sn`. Sau đó, ta đã đóng gói dữ liệu của cấu trúc `MyData` vào một mảng byte có kích thước bằng với kích thước của cấu trúc `MyData`. Để đóng gói dữ liệu này, ta đã sử dụng hàm `memcpy` để sao chép dữ liệu của cấu trúc `MyData` vào mảng byte `buffer`.

Sau khi đóng gói dữ liệu, ta đã sử dụng hàm `send` để gửi mảng byte `buffer` qua Ethernet. Hàm `send` sẽ trả về số byte đã được gửi, nếu trả về giá trị âm thì có nghĩa là có lỗi xảy ra.

Sau khi gửi dữ liệu, ta đã đóng kết nối bằng cách sử dụng hàm `close`.

Trên phía máy chủ, ta cũng có thể sử dụng cùng một cấu trúc dữ liệu để giải mã dữ liệu nhận được từ Ethernet. Bạn có thể sử dụng hàm `recv` để nhận dữ liệu qua Ethernet, sau đó sử dụng hàm `memcpy` để sao chép dữ liệu vào cấu trúc `MyData`. 

## Ví dụ mã nguồn cho phía máy chủ như sau:

c++

```c
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

struct MyData {
    int id;
    int test;
    int box;
    char sn[21];
};

int main() {
    // tạo socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // thiết lập địa chỉ và cổng của máy chủ
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // liên kết địa chỉ với socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // lắng nghe kết nối từ máy khách
    if (listen(sockfd, 1) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // chấp nhận kết nối từ máy khách
    int clientfd = accept(sockfd, NULL, NULL);
    if (clientfd < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // nhận dữ liệu từ máy khách
    char buffer[sizeof(MyData)];
    int numbytes = recv(clientfd, buffer, sizeof(buffer), 0);
    if (numbytes < 0) {
        perror("receive failed");
        exit(EXIT_FAILURE);
    
    // giải mã dữ liệu nhận được
    MyData data;
    memcpy(&data, buffer, sizeof(data));

    // in ra các trường của cấu trúc MyData
    cout << "id: " << data.id << endl;
    cout << "test: " << data.test << endl;
    cout << "box: " << data.box << endl;
    cout << "sn: " << data.sn << endl;

    // đóng kết nối
    close(clientfd);
    close(sockfd);

    return 0;
}
```

Trong mã nguồn trên, ta đã sử dụng hàm `accept` để chấp nhận kết nối từ máy khách. Sau đó, ta sử dụng hàm `recv` để nhận dữ liệu từ máy khách. Hàm `recv` sẽ trả về số byte đã nhận được, nếu trả về giá trị âm thì có nghĩa là có lỗi xảy ra.

Sau khi nhận được dữ liệu, ta đã sử dụng hàm `memcpy` để sao chép dữ liệu từ mảng byte `buffer` vào cấu trúc `MyData`. Cuối cùng, ta đã in ra các trường của cấu trúc `MyData`, sau đó đóng kết nối bằng cách sử dụng hàm `close`.

Trên đây là một ví dụ đơn giản về cách gửi và nhận dữ liệu qua Ethernet bằng một cấu trúc dữ liệu thay vì sử dụng JSON. Tuy nhiên, sử dụng JSON có thể giúp ta dễ dàng đóng gói và giải mã dữ liệu hơn, đồng thời giúp ta tránh được các lỗi phát sinh do sai sót trong việc đóng gói và giải mã dữ liệu.
