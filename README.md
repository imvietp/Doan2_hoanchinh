![website scheme](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/6c82d8f1-1799-4262-842e-b66e8a816d57)CHƯƠNG 3: THIẾT KẾ KIẾN TRÚC HỆ THỐNG

3.1. THIẾT KẾ PHẦN CỨNG

3.1.1.	Sơ đồ khối 

Hệ thống bao gồm 6 khối chính sau đây:

 ![diagram](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/43d32b46-0b3b-40c4-906d-06dfdc17dc53)


Hình 3.1. Sơ đồ khối hệ thống

- Khối xử lý trung tâm: ESP32 đóng vai trò là trung tâm của hệ thống điều khiển bể cá, giúp tối ưu hóa quá trình nuôi cá thông qua nhiều chức năng đa dạng. Với khả năng kết nối Wi-Fi và thông qua website, ESP32 cho phép người nuôi cá điều khiển bơm và van xả nước dựa vào mực nước tự động và thủ công, nhận dữ liệu từ các cảm biến và gửi nó đến Firebase
- Khối cảm biến: Bao gồm cảm biến siêu âm có tính chính xác cao, dùng để thu thập dữ liệu từ đó đưa tín hiệu về khối xử lý trung tâm, rồi sau đó khối xử lý trung tâm sẽ xử lý Khối cảm biến trong hệ thống điều khiển bể cá thông minh có nhiệm vụ đo lường và cung cấp thông tin về mức độ nước, độ đục, nhiệt độ, thời gian thực của hồ cá
Khối công suất: kết hợp với relay được sử dụng trong các ứng dụng điện tử để chuyển đổi tín hiệu điều khiển từ các bộ vi xử lý hoặc các thiết bị đầu vào khác sang các tín hiệu điện áp cao hơn để điều khiển các thiết bị công suất lớn hơn, khối công suất kết hợp với relay được sử dụng để điều khiển máy bơm mini và servo
- Khối hiển thị LCD: trong mô hình hệ thống bơm xả nước tự động cho hồ cá được sử dụng để hiển thị các thông tin về thời gian thực
- Khối động cơ: máy bơm trong mô hình này là máy bơm mini 12V, sử dụng để bơm nước trong hồ cá. Khi tín hiệu điều khiển được truyền từ khối xử lý trung tâm (ESP32) đến khối công suất kết hợp với relay, relay sẽ kích hoạt khối động cơ máy bơm và ngoài ra còn là động cơ servo hoạt động khi cho cá ăn.
- Khối nguồn: Khối nguồn trong mô hình hệ thống hồ cá có chức năng cung cấp điện cho toàn bộ hệ thống, bao gồm các linh kiện và khối động cơ. Khối nguồn là 5V cho cả hệ thống
Khối cơ sở dữ liệu Firebase (realtime database):
-	Khối Firebase Realtime đóng vai trò quan trọng trong hệ thống điều khiển bể cá thông minh, cung cấp một cơ sở dữ liệu đồng bộ và thời gian thực giữa hệ thống và website điều khiển. Với tích hợp Firebase Realtime, hệ thống có khả năng truyền và nhận dữ liệu nhanh chóng, giúp người dùng dễ dàng điều khiển bơm và van xả nước dựa vào mực nước tự động và thủ công, đo độ đục, cho cá ăn, và giám sát nhiệt độ môi trường nước.
-	Thông qua Firebase Realtime, trạng thái của hệ thống và các dữ liệu liên quan được cập nhật liên tục, và người dùng có thể truy cập vào website điều khiển để theo dõi và điều khiển từ xa các chức năng của hệ thống. Khi người dùng thực hiện điều khiển, thông tin sẽ được gửi và cập nhật trực tiếp lên Firebase Realtime, từ đó kích hoạt các hành động tương ứng trên hệ thống điều khiển bể cá.
Khối Website: Khối website trong hệ thống điều khiển bể cá thông minh là giao diện người dùng trực quan và tiện lợi, cung cấp khả năng điều khiển và giám sát toàn diện cho bể cá thông qua mạng Internet. Với tích hợp các chức năng điều khiển và giám sát, người nuôi cá có thể dễ dàng quản lý bể cá và các thông số liên quan để tạo điều kiện sống tốt nhất cho cá cảnh của mình.

3.1.2.	Sơ đồ nguyên lý của hệ thống

Dưới đây là sơ đồ nguyên lý của toàn bộ hệ thống:

![schematic](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/5ecba72e-70e1-41bf-8b0c-a53b89d6d0d0)

 
Hình 3.2. Sơ đồ nguyên lý hệ thống









3.1.3.	Lưu đồ thuật toán của chương trình chính
Dưới đây là lưu đồ thuật toán của chương trình chính:

![flow diagram](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/05d2d713-f224-410d-97e0-ab3de0f62a9b)

 
Hình 3.3. Lưu đồ thuật toán hệ thống
Giải thích chi tiết lưu đồ thuật toán của hệ thống:
1.	Khởi tạo hệ thống:
-	Bắt đầu chạy chương trình.
-	Kết nối và cấu hình ESP32 với mạng Wi-Fi.
-	Thiết lập kết nối với Firebase Realtime Database.
2.	Đọc dữ liệu từ Firebase:
-	Kiểm tra trạng thái chế độ tự động/cho cá ăn
3.	Thu thập dữ liệu độ đục, nhiệt độ từ cảm biến:
-    Đọc giá trị độ đục từ cảm biến.
-    Đọc giá trị nhiệt độ môi trường nước từ cảm biến.
4.   Điều khiển bơm và van xả nước dựa vào mực nước nếu auto mode == ON
So sánh mức nước hiện tại với giá trị mực nước được cấu hình.
-	Nếu mức nước quá cao, tắt bơm hoặc mở van xả nước để giảm mức nước.
-	Nếu mức nước quá thấp, kích hoạt bơm hoặc đóng van để bơm thêm nước.
5.   Điều khiển bơm và van xả nước thủ công:
-  Đọc tín hiệu từ website để xác định lệnh điều khiển từ người dùng.
Thực hiện điều khiển bơm và van xả nước theo lệnh đã nhận.
      6. Bật servo nếu feed == ON 
      7. Cập nhật dữ liệu lên Firebase:
      - Cập nhật giá trị mực nước, độ đục, nhiệt độ môi trường nước, trạng thái bơm và van lên Firebase Realtime Database.
      8. Lặp lại quá trình:
Quay lại bước 2 để lặp lại quá trình đọc và điều khiển hệ thống theo thời gian thực.







3.1.4.	Thiết kế mạch PCB

Dưới đây là mạch PCB của hệ thống ở dạng 3D:
![3D PCB](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/5a6ce7e9-86d6-4fd3-a3a0-3fa52684bc93)

Hình 3.4. Thiết kế PCB của mạch tổng dạng 3D

      Mạch mô phỏng PCB của hệ thống nhỏ gọn, sắp xếp linh kiện hợp, các linh kiện được lắp dễ nhìn. 
      Ở bên trái là ESP32, các đầu ra các cảm biến siêu âm, module đo đục, LCD, nhiệt độ. Ở bên phải là 2 relay máy bơm và xả, và cấp nguồn 5V.

 ![top layer](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/e3024731-6c80-4f53-ab93-49e061848393)

Hình 3.5. Thiết kế PCB của mạch tổng dạng 2D (top)
![bottom layer](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/c032a0ab-b8e1-4157-b24a-bab11634db72)

Hình 3.6. Thiết kế PCB của mạch tổng dạng 2D (bottom)
-	Với kích thước nhỏ gọn và các linh kiện sắp xếp hợp lý
-	Kích thước chiều dài: 9.9cm 
-	Kích thước chiều rộng: 8.1cm


 

3.2.4. Giao diện và chức năng Website

- Giao diện trang Home: quan sát và xem thời gian hệ thống
 ![website scheme](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/da593108-2d8b-4c35-82ec-c1572729c09b)

Hình 3.10. Giao diện Website trang HOME
- Giao diện trang Temperature: giám sát nhiệt độ trong nước
 ![Temp](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/523746c3-f75b-419c-9bf5-8502b5cb97a6)

Hình 3.11. Giao diện Website trang TEMPERATURE
- Giao diện trang Turbidity: giám sát độ đục trong nước
 ![tur](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/957b1330-0997-4c5b-a370-49a2e72b4d77)

Hình 3.12. Giao diện Website trang TURBIDITY
- Giao diện trang Pump: điều khiển hệ thống bơm, bật tắt chế độ tự động và bật tắt máy bơm xả, bên cạnh là hình ảnh hiển thị trạng thái mực nước 
 ![pump](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/5ce1a37f-9502-4db9-a1cb-f2d45438b80d)

Hình 3.13. Giao diện Website trang PUMP
- Giao diện trang Feed: bật tắt cho cá ăn 
 ![feed](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/ad936a98-d7b0-46ec-b82f-b3cb52b833ea)

Hình 3.14. Giao diện Website trang FEED
![feed](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/66360d96-fcd2-43ca-9457-4eee7646dc24)

