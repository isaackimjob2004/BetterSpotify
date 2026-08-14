# Create a VCS for making playlists online

### Libraries / APIs

use libgit2 library for Git functionality in backend

Spotify Web API, Apple Music API, and Youtube Data API can be used to link songs. Some restrictions or workarounds so we should start with mock data.

---

### User experience

This app should be cross platform, so it can work with anyones music subscription. Created playlists must be stored here and its a bonus if that same playlist can be sent over to a respective app.

Store playlists as simple JSON or YAML files inside Git repos.

Use a universal identifier for a song. Maybe ISRC?

---

### Git Features -> Music

Repos are containers that hold all files, history, and metadata for a playlist
**A repo is one playlist (curated album)**. Stores playlist.json file
When a user creates a new playlist, backend initializes a bare Git repo. The JSON file tracks data like ISRC, title, platform, duration

**A commit is a snapshot of the repo/playlist**. This is accompanied by a commit msg and author name
Users should be able to make local changes to their local version of the repo, to which they can commit.
For now lets ignore the differences between a local repo vs a remote repo. They are the same thing to avoid confusion for users. So make a change, it appears on the playlist on the internet. But they have to commit that change before it is applied online, else it remains on their version of the playlist.

**playlists have histories** and they can see them. Probably void commit msgs or just make them optional. Or have a list of options that they can select for messages. With histories, users can rewind playlists.

**Cloning and forking** is when users create a personal copy of someone else's playlist. A spinoff mechanism

**Branching allows parallel development**. A PR asks the owner of the main branch to merge your changes in. This is a suggestion / collaboration feature.

**Diffs** would be a preview changes view. Og creator seens new songs highlighted in green and suggested removals in red. Songs should be sorted in some manner.

**Git Blame** type of feature where next to each song in a playlist, users can see who added it, who approved it, and who likes it

**Git merge** must be done so it is automated and easy for playlist curators. 
