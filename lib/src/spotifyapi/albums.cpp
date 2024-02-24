#include "lib/spotify/api.hpp"

void lib::spt::api::album(const std::string &id, lib::callback<lib::spt::album> &callback)
{
	get(lib::fmt::format("albums/{}", id), callback);
}

void lib::spt::api::album_tracks(const lib::spt::album &album,
	lib::callback<std::vector<lib::spt::track>> &callback)
{
	get_items(lib::fmt::format("albums/{}/tracks?limit=50", album.id),
		[album, callback](const std::vector<lib::spt::track> &results)
		{
			std::vector<lib::spt::track> tracks;
			tracks.reserve(results.size());
			for (const auto &result: results)
			{
				lib::spt::track track = result;
				track.album.name = album.name;
				tracks.push_back(track);
			}
			callback(tracks);
		});
}

void lib::spt::api::album_tracks(const spt::album &album, const paged_callback<spt::track> &callback) const
{
	const auto albumName = album.name;
	const auto url = fmt::format("albums/{}/tracks?limit=50", album.id);

	request.get_page<spt::track>(url, {},
		[callback, albumName](const result<page<spt::track>> &result) -> bool
		{
			if (!result.success())
			{
				return callback(result);
			}

			auto &page = result.value();
			for (auto &item: page.items)
			{
				item.album.name = albumName;
			}

			return callback(result);
		});
}
