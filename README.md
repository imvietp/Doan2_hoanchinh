3.1. THIẾT KẾ PHẦN CỨNG

1.1.1.	Sơ đồ khối 

Hệ thống bao gồm 6 khối chính sau đây:
![diagram](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/67fec7e5-9923-4390-82d2-77007ba51731)

- Khối xử lý trung tâm: ESP32 đóng vai trò là trung tâm của hệ thống điều khiển bể cá, giúp tối ưu hóa quá trình nuôi cá thông qua nhiều chức năng đa dạng. Với khả năng kết nối Wi-Fi và thông qua website, ESP32 cho phép người nuôi cá điều khiển bơm và van xả nước dựa vào mực nước tự động và thủ công, nhận dữ liệu từ các cảm biến và gửi nó đến Firebase
Khối cảm biến: Bao gồm cảm biến siêu âm có tính chính xác cao, dùng để thu thập dữ liệu từ đó đưa tín hiệu về khối xử lý trung tâm, rồi sau đó khối xử lý trung tâm sẽ xử lý Khối cảm biến trong hệ thống điều khiển bể cá thông minh có nhiệm vụ đo lường và cung cấp thông tin về mức độ nước, độ đục, nhiệt độ, thời gian thực của hồ cá
Khối công suất: kết hợp với relay được sử dụng trong các ứng dụng điện tử để chuyển đổi tín hiệu điều khiển từ các bộ vi xử lý hoặc các thiết bị đầu vào khác sang các tín hiệu điện áp cao hơn để điều khiển các thiết bị công suất lớn hơn, khối công suất kết hợp với relay được sử dụng để điều khiển máy bơm mini và servo
- Khối hiển thị LCD: trong mô hình hệ thống bơm xả nước tự động cho hồ cá được sử dụng để hiển thị các thông tin về thời gian thực
Khối động cơ: máy bơm trong mô hình này là máy bơm mini 12V, sử dụng để bơm nước trong hồ cá. Khi tín hiệu điều khiển được truyền từ khối xử lý trung tâm (ESP32) đến khối công suất kết hợp với relay, relay sẽ kích hoạt khối động cơ máy bơm và ngoài ra còn là động cơ servo hoạt động khi cho cá ăn.
- Khối nguồn: Khối nguồn trong mô hình hệ thống hồ cá có chức năng cung cấp điện cho toàn bộ hệ thống, bao gồm các linh kiện và khối động cơ. Khối nguồn là 5V cho cả hệ thống
Khối cơ sở dữ liệu Firebase (realtime database):
-	Khối Firebase Realtime đóng vai trò quan trọng trong hệ thống điều khiển bể cá thông minh, cung cấp một cơ sở dữ liệu đồng bộ và thời gian thực giữa hệ thống và website điều khiển. Với tích hợp Firebase Realtime, hệ thống có khả năng truyền và nhận dữ liệu nhanh chóng, giúp người dùng dễ dàng điều khiển bơm và van xả nước dựa vào mực nước tự động và thủ công, đo độ đục, cho cá ăn, và giám sát nhiệt độ môi trường nước.
-	Thông qua Firebase Realtime, trạng thái của hệ thống và các dữ liệu liên quan được cập nhật liên tục, và người dùng có thể truy cập vào website điều khiển để theo dõi và điều khiển từ xa các chức năng của hệ thống. Khi người dùng thực hiện điều khiển, thông tin sẽ được gửi và cập nhật trực tiếp lên Firebase Realtime, từ đó kích hoạt các hành động tương ứng trên hệ thống điều khiển bể cá.
Khối Website: Khối website trong hệ thống điều khiển bể cá thông minh là giao diện người dùng trực quan và tiện lợi, cung cấp khả năng điều khiển và giám sát toàn diện cho bể cá thông qua mạng Internet. Với tích hợp các chức năng điều khiển và giám sát, người nuôi cá có thể dễ dàng quản lý bể cá và các thông số liên quan để tạo điều kiện sống tốt nhất cho cá cảnh của mình.


1.1.2.	Sơ đồ nguyên lý của hệ thống

Dưới đây là sơ đồ nguyên lý của toàn bộ hệ thống:

![schematic](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/0da4974a-9c6a-41aa-a7e5-296a28604ca9)

1.1.3.	Lưu đồ thuật toán của chương trình chính

Dưới đây là lưu đồ thuật toán của chương trình chính:

![flow diagram](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/d234c6cf-b475-481c-89a3-9ca2d01f22c7)


1.1.4.	Thiết kế mạch PCB

Dưới đây là mạch PCB của hệ thống ở dạng 3D:

![3D PCB](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/c850dd72-d451-496e-8ead-a405b55658d1)

Top layer:

![top layer](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/c59e96c0-b506-4db1-8bd3-644181d8c87f)

Bottom layer:

![bottom layer](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/2a53888f-7b65-4ceb-b067-a4c7d92e1c6f)

1.1.5.	Design a DIY website
Overall:

![website scheme](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/a060551b-94d0-4568-af67-1abede94239c)

Temperature display:

![Temp](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/d45fa574-ca68-4ea0-a45c-932b5e72723c)

Turbidity display:

![tur](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/e7e7fdde-50e3-48f4-a0fa-eed2cb4289a7)

Feeding display:

![feed](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/01850de2-e595-4ed8-8ff9-53633b017092)



Overall product:


![sp1](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/71544071-1143-44df-b364-5a63c0ba07e1)


![sp2](https://github.com/imvietp/Doan2_hoanchinh/assets/125435826/53f10b40-c71c-4355-9fbb-85bd2ae95aee)
