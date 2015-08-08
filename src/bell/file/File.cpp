#include <fstream>
#include "File.hpp"
#include "FileException.hpp"
#include "../Logger.hpp"

using namespace std;

namespace bell { namespace file {
	//	実体
	struct File::Impl final {
		string			name;
		vector<byte>	data;

		explicit Impl(string name, vector<byte> data)
			: name(move(name)), data(move(data)) {}
	};


	//	コンストラクタ
	File::File(shared_ptr<Impl> impl) noexcept
		: impl_(move(impl)) {}


	//	開く
	File File::open(boost::string_ref path) {
		logger::write(u8"ファイルの読み込み path:%1%", path);

		string name = path.to_string();

		//	ファイルを開く
		ifstream ifs{ name, ios::binary };
		if(!ifs) {
			logger::writeError(u8"失敗");
			BELL_THROW(FileException, path, "Failed to open.");
		}

		//	サイズの取得
		auto size = ifs.seekg(0, ios::end).tellg();
		ifs.seekg(0, ios::beg);

		//	バッファの確保
		vector<byte> buffer;
		buffer.resize(static_cast<vector<byte>::size_type>(size));

		//	読み込み
		ifs.read(reinterpret_cast<char*>(&buffer[0]), size);

		logger::write(u8"完了");

		return File{
			make_shared<Impl>(
				move(name),
				move(buffer))
		};
	}


	//	FromMemory
	File File::openFromMemory(boost::string_ref name, ArrayRef<byte> data) {
		return File{
			make_shared<Impl>(
				move(name.to_string()),
				move(data.toVector()))
		};
	}


	//	ファイル名
	boost::string_ref File::name() const noexcept {
		return impl_->name;
	}


	//	データ
	ArrayRef<byte> File::data() const noexcept {
		return impl_->data;
	}
}}
