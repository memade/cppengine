#if !defined(AFX_SK_H__95861FD3_A89B_4309_9DC9_DC103D54A901__HEAD__)
#define AFX_SK_H__95861FD3_A89B_4309_9DC9_DC103D54A901__HEAD__

namespace local {
	class Global final {
	public:
		Global();
		~Global();
	public:
		static std::string Encode6Bit(const std::string& strSrc);
		static std::string Decode6Bit(const std::string& in);
	};
}///namespace local

/*!@ 新生联创®（上海）*/
/*!@ Sat May 22 12:13:48 UTC+0800 2021*/
/*!@ ___www.skstu.com___*/
#endif /*AFX_SK_H__95861FD3_A89B_4309_9DC9_DC103D54A901__HEAD__*/