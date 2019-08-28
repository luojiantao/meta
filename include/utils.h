﻿#pragma once
#include <spdlog/spdlog.h>
#include <string>
#include <clang-c/Index.h>
#include <optional>

namespace meta::utils
{
	std::string to_string(const CXCursor& _in_cursor);
	std::string to_string(const CXString &str);
	std::string to_string(const CXType& _in_type);
	std::string full_name(const CXType& _in_type);
	std::string to_string(CXTemplateArgumentKind _in_kind);
	std::string to_string(CXTypeKind _in_kind);
	const std::string& full_name(CXCursor in_cursor);
	std::string join(const std::vector<std::string>& param, const std::string& sep);
	const std::string& to_string(CXCursorKind _in_kind);
	spdlog::logger& get_logger();
	class cursor_hash
	{
	public:
		std::size_t operator()(const CXCursor& in_cursor) const;

	};
	class cursor_equal
	{
	public:
		bool operator()(const CXCursor& from, const CXCursor& to) const;
	};
	class cxtype_hash
	{
	public:
		std::size_t operator()(const CXType& in_type) const;
	};
	class cxtype_equal
	{
	public:
		bool operator()(const CXType& type_1, const CXType& type_2) const;
	};
	class template_types
	{
	public:
		static template_types& instance();
		bool add_type(const CXCursor& template_name_cursor);
		const std::string& get_type(const CXType& cur_type) const;
		std::vector<std::string> all_values() const;
	private:
		template_types();
		std::unordered_map<CXType, std::string, cxtype_hash, cxtype_equal> _type_cache;
	};
	std::vector<CXCursor> cursor_get_children(CXCursor parent);
	CXTypeKind expect_std_int(CXType int_type);

	// the annotation should be (item1, item2, item3(key_1, key_2, key_3 = value_3))
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> parse_annotation(const std::string& cur_annotation);
}
