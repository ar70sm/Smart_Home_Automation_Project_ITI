# Smart Home Automation Project

(ITI graduation project)
[Explanatory Videos](https://drive.google.com/drive/folders/1T_dZeL-VsLNtljzIJPahGyp_KcfCCxDy)
---
## Project Team
-  [Eng. Abd Alrahman Ashraf Mohamed](https://www.linkedin.com/in/ar70sm)
-  [Eng. El-Sayed Talaat El-Sayed Tamam](https://www.linkedin.com/in/el-sayed-talaat-b18842284)

## Project Summary

The Smart Home Embedded System Project is an innovative endeavor focused on enhancing residential living through advanced automation and control. This project aims to optimize indoor temperature regulation based on user-defined preferences while providing secure management of various household functions. Key project components include robust security measures, versatile control options, an intelligent weather control system, and an efficient garage management system. By seamlessly integrating these features, this project promises to elevate the comfort, security, and convenience of modern smart homes.

## Security Measures

To ensure the security of the system, the following measures have been implemented:

- During the initial setup, the user sets a password, which is stored in the EEPROM.
- Subsequent access to the system requires the user to enter the password.
- If the user exceeds the allowed number of login attempts, the system enforces a predetermined timeout period (typically around 20 seconds) before further access attempts are permitted.

## Control Features
The system provides adaptable control functionalities that cater to both analog and digital input requirements. The subsequent examples demonstrate the utilization of each type:
- **Analog Input:** Users have the flexibility to specify their preferred temperatures for each room.
- **Digital Input:** Users can manage a variety of household appliances, including doors, televisions, lights, and more, by simply toggling them on or off.
Furthermore, the system is intentionally designed for extensibility, enabling developers to seamlessly integrate new functionalities that necessitate specific value inputs (analog) or straightforward on/off control (digital).

## Weather Control System

The weather control feature allows users to set their desired room temperature. If the room temperature deviates by a predefined threshold (typically two degrees), the system responds as follows:

- **Cooling:** If the temperature exceeds the set value, the chiller is activated to bring the room temperature back within the desired range.
- **Heating:** If the temperature falls below the specified degree, the heater is activated to restore the desired temperature.
- **Temperature Alarm:** The system triggers an alarm if the temperature surpasses a certain predefined level.

## Garage Management

The garage management system comprises entry sensors, exit sensors, and N number of sensors for each parking space to determine occupancy status. Key functions include:

- Access Control: The system prevents any vehicle from entering the garage without authorization from the user via the master control interface.
- Occupancy Management: Entry to any parking space is only allowed if there is an available parking spot.
- Entry Process: Upon detecting a vehicle, the entry sensor opens the garage door and keeps it open until one of the parking space sensors confirms successful parking.
- Exit Process: The exit sensor facilitates safe vehicle exit by opening the garage door and keeping it open until a parking space sensor confirms the exit.
- Real-time Monitoring: Users can monitor the number of parked cars in the garage, their respective locations, and available parking spaces via a dedicated screen.


This Smart Home Automation project represents an advanced and adaptable solution for enhancing home comfort, security, and energy efficiency. It provides a robust framework for integrating various control and monitoring functions, offering users the convenience of a modern smart home system.
