# ppvis_training_1
A training task for the PPvIS exam (3rd semester)

Notes:
1. Some entity classes have friends (interfaces) with which they shouldn't connect directly (e.g `IllustratorInterface` is a friend of `Document`). 
I know it's bad. Ideally there should be an abstraction between the entity and the interface, too, it seemed overkill to me at first, and when I stumbled across
hardcode and tight coupling of the classes (unnecessary friendships) it was too late to fix it.
2. It is mostly the same reason I didn't create iterators over `Catalogues` and `Files`. When I've realized I have 4 functions with nearly the same code to iterate
over the filesystem tree, it was 2 hours before the deadline. Lesson learned, I guess? Could have also used lambdas for this, but we didn't have it in the labs, so I didn't risk to.
3. I wrote some tests btw (command for compiling the project is on the screenshot, too)
![image](https://github.com/FallenChromium/ppvis_training_1/blob/main/screenshots/tests.png?raw=true)

