#pragma once

#include <string>

#include "players.hh"
#include "hiscore.hh"
#include "songitems.hh"

#include "fs.hh"

/**Access to a database for performous which holds
  Player-, Hiscore-, Song-, Track- and (in future)
  Partydata.

  This is a facade for Players, Hiscore and SongItems.

  Will be initialized at the very beginning of
  the program.*/
class Database
{
  public:
	/**Will try to load the database.
	  If it does not succeed the error will be ignored.
	  Only some information will be printed on stderr.
	  */
	Database (fs::path filename);
	/**Will try to save the database.
	  This will even be done if the loading failed.
	  It tries to create the directory above the file.
	  */
	~Database ();

	/**Loads the whole database from xml.
	  @exception bad_cast may be thrown if xml element is not of correct type
	  @exception xmlpp exceptions may be thrown on any parse errors
	  @exception PlayersException if some conditions of players fail (e.g. no id)
	  @exception HiscoreException if some hiscore conditions fail (e.g. score too high)
	  @exception SongItemsExceptions if some songs conditions fail (e.g. no id)
	  @post filled database
	  */
	void load();
	/**Saves the whole database to xml.
	  Will write out everything to the file given in the constructor, @see file()
	*/
	void save();

	/**The filename given by the constructor.
	  @returns the filename used for the database.
	  */
	std::string file();

  public: // methods for database management

	/**A facade for Players::addPlayer.*/
	void addPlayer (std::string const& name, std::string const& picture = "", int id = -1);
	/**A facade for SongItems::addSong.*/
	void addSong (boost::shared_ptr<Song> s);
	/**A facade for Hiscore::addHiscore.
	 The ids will be looked up first by using the songs and current players data.*/
	void addHiscore (boost::shared_ptr<Song> s);

  public: // methods for database queries
	/**A facade for Hiscore::reachedHiscore.
	  Queries if the current player with current score has reached a new hiscore
	  for the song s.
	 */
	bool reachedHiscore (boost::shared_ptr<Song> s);

	friend int test(std::string const&, int);

  private:
	fs::path m_filename;

	Players m_players;
	Hiscore m_hiscores;
	SongItems m_songs;
};