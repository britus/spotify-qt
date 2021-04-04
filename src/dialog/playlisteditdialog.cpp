#include "playlisteditdialog.hpp"

PlaylistEditDialog::PlaylistEditDialog(spt::Spotify *spotify, const lib::spt::playlist &playlist,
	int selectedIndex, QWidget *parent)
	: QDialog(parent)
{
	auto playlistName = QString::fromStdString(playlist.name);
	auto playlistDescription = QString::fromStdString(playlist.description);

	setWindowTitle(playlistName);
	setModal(true);
	auto layout = new QVBoxLayout(this);

	// Name
	layout->addWidget(new QLabel("Name:", this));
	name = new QLineEdit(playlistName, this);
	layout->addWidget(name);

	// Description
	layout->addWidget(new QLabel("Description:", this));
	description = new QTextEdit(playlistDescription, this);
	layout->addWidget(description);

	// Toggles
	auto toggles = new QHBoxLayout();
	toggles->setAlignment(Qt::AlignLeft);
	isPublic = new QCheckBox("Public", this);
	isPublic->setChecked(playlist.is_public);
	toggles->addWidget(isPublic);
	isCollaborative = new QCheckBox("Collaborative", this);
	isCollaborative->setChecked(playlist.collaborative);
	toggles->addWidget(isCollaborative);
	layout->addLayout(toggles);

	// Focus depending on selected index
	if (selectedIndex < 0)
		setFocus();
	else if (selectedIndex == 0)
		name->setFocus();
	else if (selectedIndex == 1)
		description->setFocus();

	// Dialog buttons
	auto buttons = new QDialogButtonBox(this);
	buttons->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	QDialogButtonBox::connect(buttons, &QDialogButtonBox::accepted, [this, playlist, spotify]
	{
		auto pl = playlist;
		pl.name = name->text().toStdString();
		pl.description = description->toPlainText().toStdString();
		pl.is_public = isPublic->isChecked();
		pl.collaborative = isCollaborative->isChecked();

		spotify->edit_playlist(pl, [this](const std::string &result)
		{
			if (result.empty())
			{
				accept();
				return;
			}

			QMessageBox::warning(this, "Edit failed",
				QString("Failed to save changes: %1")
					.arg(QString::fromStdString(result)));
		});
	});

	QDialogButtonBox::connect(buttons, &QDialogButtonBox::rejected, [this]
	{
		reject();
	});

	layout->addWidget(buttons);
	setLayout(layout);
}