from locust import HttpLocust, TaskSet, task, between
import lxml.html


class UserBehavior(TaskSet):
    def on_start(self):
        self.client.get("/")

    @task(1)
    def investigationPage(self):
        root = self.getRoot("/index.php?board=23.0")
        links = root.xpath("//div[@class='pagelinks']/a[last()-2]")
        href = links[0].attrib['href']
        
        self.lastPage(href, root)

    def lastPage(self, href, root):
        root = self.getRoot(href)

        # Check for the post presence
        links = root.xpath("//span[@id='msg_134347']")
        if (links != []):
            print("On the right page!")

    def getRoot(self, href):
        res = self.client.get(href)
        html = res.text
        return lxml.html.fromstring(html)


class WebsiteUser(HttpLocust):
    task_set = UserBehavior
    wait_time = between(1000, 2000)
