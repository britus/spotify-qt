#pragma once

#include "spotify/spotify.hpp"
#include "util/treeutils.hpp"
#include "lib/spotify/audiofeatures.hpp"

#include <QAbstractItemView>
#include <QDockWidget>
#include <QHeaderView>
#include <QTreeWidget>

namespace View
{
	class AudioFeatures: public QTreeWidget
	{
	Q_OBJECT

	public:
		AudioFeatures(spt::Spotify &spotify, const std::string &trackId, QWidget *parent);

	private:
		void loaded(const lib::spt::audio_features &features);
	};
}
