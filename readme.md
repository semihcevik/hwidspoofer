# HWID Spoofer

![Windows](https://img.shields.io/badge/Platform-Windows-blue) 
![x64](https://img.shields.io/badge/Architecture-x64-green)

A Windows HWID (Hardware Identification) spoofer designed to modify hardware identifiers and clean tracking traces.  
**Use at your own risk. Intended for educational/research purposes only.**

---
This project showcases my programming skills, problem-solving abilities, and interest in different areas of expertise.

## Features

### Kernel Driver (Credits: [btbd/hwid](https://github.com/btbd/hwid))
- Spoofs identifiers for:
  - Disks and volumes
  - Network Interface Cards (NIC) and ARP tables
  - SMBIOS (motherboard, BIOS, etc.)
  - Boot identifiers
  - GPU information

### Usermode Program
- Cleans registry traces related to hardware information and driver mappings
- Removes common tracking files
- **ImGui-based GUI** for user-friendly interaction

---

## ⚠️ Disclaimer
- This tool is provided **as-is** with no warranties. 
- Misuse for unethical or illegal activities (e.g., bypassing bans, license evasion) is strictly prohibited.
- The author and contributors assume **no responsibility** for damages, bans, or legal consequences arising from its use.  
**By using this software, you accept all risks and liabilities.**

---

## Compatibility
- Tested on **x64 Windows 10**:
  - Version 1507 (Build 10240)
  - Version 1809 (Build 17763.379)
  - Version 1903 (Builds 18362.30 and 18362.175)
- Partial functionality may work on older versions (untested).

---

## Usage
1. **Requirements**:
   - Administrator privileges
   - Disable Secure Boot and Driver Signature Enforcement (for driver loading)
2. Run the usermode program (GUI) to:
   - Spoof hardware IDs
   - Clean registry and tracking files
3. Reboot to apply changes.

**Note**: Antivirus software may flag this tool due to its low-level system access. Use in a controlled environment.

---

## Credits
- **Kernel Driver**: Adapted from [btbd/hwid](https://github.com/btbd/hwid).  
- **GUI**: Built with [Dear ImGui](https://github.com/ocornut/imgui).

---

## Legal
This project is intended for **educational purposes only**. Reverse-engineering and security research help improve system understanding and defensive techniques. Always comply with local laws and terms of service.

---
