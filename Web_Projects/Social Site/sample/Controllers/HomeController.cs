using sample.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace sample.Controllers
{
    public class HomeController : Controller
    {
        //can be used across all action methods in this class
        private MyDbContext db;

        /// <summary>
        /// MVC apparently needs a default constructor
        /// </summary>
        public HomeController() :this(null)  //note that calling this(null) will also call 
                                             //code inside HomeController(MyDbContext)
        {

        }

        /// <summary>
        /// Initializes the home controller with the supplied DbContext
        /// </summary>
        /// <param name="someDb"></param>
        public HomeController(MyDbContext someDb = null)
        {
            //If we were given a null context, just use the default context
            if (someDb == null)
            { 
            db = new MyDbContext("MyDbContext");
            }
            else
            {
                //otherwise, use the supplied context
                db = someDb;
            }
        }

        /// <summary>
        /// Will show a list of all users within the system
        /// </summary>
        /// <returns></returns>
        public ActionResult Index()
        {
            //query using fluent API
            List<Person> people = db.People
                .Where(p => p.Id > 0)
                .ToList();

            //query using LINQ (same as the above fluent API method)
            List<Person> people2 = (
                                    from person in db.People
                                    where person.Id > 0
                                    select person
                                   ).ToList();
            
            //return the "View" to MVC.  By default, MVC will look for a view titled
            //"index.cshtml" inside the "Views/Home" folder.  Note that we're also sending
            //a list of People objects for the view to process.
            return View(people);
        }

        /// <summary>
        /// View method to allow the creation of a new Person in the DB
        /// </summary>
        /// <returns></returns>
        public ActionResult Create()
        {
            //return the view with a newly created (and empty) Person object.
            return View(new Person());
        }

        /// <summary>
        /// Postback version of the Create action.  Note that this method will only be
        /// called on HTTP POST messages (as indicated by the [HttpPost] attribute.
        /// </summary>
        /// <param name="model"></param>
        /// <returns></returns>
        [HttpPost]
        public ActionResult Create(Person model)
        {
            //MVC uses ModelState to track the correctness of the supplied Person "model."
            //If the model is valid, it means that MVC didn't detect any errors as defined
            //in the attributes in the Person class.
            if(ModelState.IsValid)
            {
                

                //Add the person to the DB.  This queues them for insertion but doesn't
                //actually insert the value into the DB.  For that, we need the next command.


                switch (model.Totema)
                {
                    case Totema.Monkey:
                        {
                            model.image = "/Content/Pictures/Monkey.png";
                            break;
                        }
                    case Totema.Squirrel:
                        {
                            model.image = "/Content/Pictures/Squirrel.png";
                            break;
                        }

                }


                model.Str = 1;
                model.Int = 1;
                model.Vit = 1;
                int[] Friends = new int[3];
                Friends[0] = 1;
                Friends[1] = 2;
                Friends[2] = 3;

                db.People.Add(model);
                
                //tell the DB to save any queued changes.
                db.SaveChanges();

                //Once we're done, redirect to the Index action of HomeController.
                return RedirectToAction("Logon");
            }

            //If we got here, it means that the model's state is invalid.  Simply return
            //to the create page and display any errors.
            return View("Create");
        }
        
        /// <summary>
        /// This action allows the user to edit a given Person
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        public ActionResult Edit(int id)
        {
            //Find the person in the DB.  Use the supplied "id" integer as a reference.
            Person somePerson = db.People
                .Where(p => p.Id == id)     //this line says to find the person whose ID matches our parameter
                .FirstOrDefault();          //FirstOrDefault() returns either a singluar Person object or NULL
            
            //If we got NULL, it must mean that we were supplied an incorrect ID.  
            //In this case, redirect to HomeController's Index action.
            if(somePerson == null)
            {
                return RedirectToAction("Index");
            }

            //If we're here, then we must have a valid person.  Send to the "Create" view because
            //create and edit are kind of the same thing.  The 2nd parameter is the model that
            //we will be sending to the Create view.
            return View("Create", somePerson);
        }

        /// <summary>
        /// Postback version of the Edit action.  Will be called when the browser sends us information
        /// back to the server.
        /// </summary>
        /// <param name="model"></param>
        /// <returns></returns>
        [HttpPost]
        public ActionResult Edit(Person model)
        {
            //again, check modelstate to make sure everything went okay
            if(ModelState.IsValid)
            {
                //Because the item already exists in the DB, we want to tell EF that
                //one of its models has been changed.  We use this somewhat strange syntax to
                //accomplish this task.
                db.Entry(model).State = System.Data.Entity.EntityState.Modified;

                //Again, the above command adds the request to a queue.  To execute the queue,
                //we need to call SaveChanges()
                db.SaveChanges();

                //when complete, redirect to Index
                return RedirectToAction("Index");
            }

            //Things must've went bad, so send back to the Create view.
            return View("Create", model);
        }




        public ActionResult CommentCreate1(int id, int pageID, int blogID, AllClasses model)
        {
            AllClasses C = new AllClasses();

            Person user = db.People.Where(p => p.Id == id).FirstOrDefault();
            C.User = user;

            model.NewComment.AuthorName = user.Username;
            model.NewComment.UserID = id;
            model.NewComment.BlogID = blogID;
            model.NewComment.Date = DateTime.Now.ToString();
            db.Comments.Add(model.NewComment);
            db.SaveChanges();

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == user.Id) || (b.User2ID == user.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;

            C.CurrentPage = pageID;
            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("Home", C);
        }

        public ActionResult Delete(Person model)
        {
            Person somePerson = db.People
                .Where(p => (p.Id == model.Id))
                .FirstOrDefault();

            db.People.Remove(somePerson);

            db.SaveChanges();

            return RedirectToAction("Index");
        }

        public ActionResult StatForm()
        {
            return View();
        }

        public ActionResult StatForm1(int cp)
        {
            AllClasses C = new AllClasses();

            Person user = db.People.Where(p => p.Id == cp).FirstOrDefault();
            C.User = user;

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == user.Id) || (b.User2ID == user.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;



            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("StatForm", C);
        }

        public ActionResult RaiseStats1(int cp, string selected_stat, string activity, int act_time)
        {
            AllClasses C = new AllClasses();

            Person user = db.People.Where(p => p.Id == cp).FirstOrDefault();
            C.User = user;
            C.CurrentPage = cp;

            if (selected_stat == "strength")
            {
                user.Str += act_time;
            }
            if (selected_stat == "vitality")
            {
                user.Vit += act_time;
            }
            if (selected_stat == "intellect")
            {
                user.Int += act_time;
            }

            if (user.Str > 1)
            {
                if (user.Int > 1 && user.Vit > 1)
                {
                    user.image = "/Content/pictures/SSayan.jpg";
                }
                else if (user.Int > 1)
                {
                    user.image = "/Content/pictures/Monkey_i_s.png";
                }
                else if (user.Vit > 1)
                {
                    user.image = "/Content/pictures/Monkey_v_s.png";
                }
                else
                {
                    user.image = "/Content/pictures/Monkey_s.png";
                }
            }
            else if (user.Vit > 1)
            {
                if (user.Int > 1)
                {
                    user.image = "/Content/pictures/Monkey_i_v.png";
                }
                else
                {
                    user.image = "/Content/pictures/Monkey_v.png";
                }
            }
            else if (user.Int > 1)
            {
                user.image = "/Content/pictures/Monkey_i.png";
            }
            else
            {
                user.image = "/Content/pictures/Monkey.png";
            }
            
            Blog Bupdate = new Blog();
            Bupdate.AuthorID = user.Id;
            Bupdate.AuthorName = user.Username;
            Bupdate.Date = DateTime.Now.ToString();
            Bupdate.HPage = user.Id;
            Bupdate.Text = user.Username + " " + activity + " and gained " + act_time + " " + selected_stat + "!";
            db.Blogs.Add(Bupdate);
            db.SaveChanges();



            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == user.Id) || (b.User2ID == user.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;



            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("Home", C);
        }

        public ActionResult BlogCreate1(int id, int pageID, AllClasses model)
        {
            AllClasses C = new AllClasses();

            Person user = db.People.Where(p => p.Id == id).FirstOrDefault();
            C.User = user;

            model.NewBlog.AuthorName = user.Username;
            model.NewBlog.AuthorID = id;
            model.NewBlog.HPage = pageID;
            model.NewBlog.Date = DateTime.Now.ToString();
            db.Blogs.Add(model.NewBlog);
            db.SaveChanges();

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == user.Id) || (b.User2ID == user.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;

            C.CurrentPage = pageID;
            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("Home", C);
        }

        public ActionResult Home(int pid, int page)
        {
            Person somePerson = db.People.Where(p => (p.Id == pid)).FirstOrDefault();

            // Setup All Classes
            AllClasses C = new AllClasses();
            C.User = somePerson;
            C.CurrentPage = page;

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == somePerson.Id) || (b.User2ID == somePerson.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;



            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("Home", C);
        }

        public ActionResult BlogDelete1(int id, int pageID, int blogID, AllClasses model)
        {
            AllClasses C = new AllClasses();

            Person user = db.People.Where(p => p.Id == id).FirstOrDefault();
            C.User = user;

            Blog delBlog = db.Blogs
                .Where(b => (b.Id == blogID))
                .FirstOrDefault();

            foreach (Comment c in db.Comments)
            {
                if (c.BlogID == blogID)
                {
                    db.Comments.Remove(c);
                }
            }

            db.Blogs.Remove(delBlog);

            db.SaveChanges();

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == user.Id) || (b.User2ID == user.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;

            C.CurrentPage = pageID;
            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("Home", C);
        }

        public ActionResult CommentDelete1(int id, int pageID, int ComID, AllClasses model)
        {
            AllClasses C = new AllClasses();

            Person user = db.People.Where(p => p.Id == id).FirstOrDefault();
            C.User = user;

            Comment delComm = db.Comments
                .Where(c => (c.Id == ComID))
                .FirstOrDefault();

            db.Comments.Remove(delComm);

            db.SaveChanges();

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == user.Id) || (b.User2ID == user.Id)).ToList();
            C.InstanceList = CI;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;

            C.CurrentPage = pageID;
            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();

            return View("Home", C);
        }







        public ActionResult Logon()
        {
            return View(new Person());
        }

        [HttpPost]
        public ActionResult Logon(Person user)
        {

            // Check User
            Person somePerson = db.People
                .Where(p => (p.Password == user.Password) && (p.Email == user.Email))
                .FirstOrDefault();



            if (somePerson != null)
            {

                // Setup All Classes
                AllClasses C = new AllClasses();
                C.User = somePerson;
                C.CurrentPage = somePerson.Id;

                List<Person> U = db.People
               .Where(b => b.Id > 0)
               .ToList();
                C.UserList = U;

                List<Blog> blgs = db.Blogs
                .Where(b => b.Id > 0)
                .ToList();
                C.BlogList = blgs;

                List<Comment> coms = db.Comments
                .Where(b => b.Id > 0)
                .ToList();
                C.CommentList = coms;

                List<ChatInstance> CI = db.Instances
                 .Where(b => (b.User1ID == somePerson.Id) || (b.User2ID == somePerson.Id))
                 .ToList();
                C.InstanceList = CI;
            
                List<ChatMessage> CM = db.Messages
               .Where(b => b.Id > 0)
               .ToList();
                C.MessageList = CM;

                List<Friend> F = db.Friends
               .Where(b => b.Id > 0)
               .ToList();
                C.FriendList = F;



                C.NewBlog = new Blog();
                C.NewComment = new Comment();
                C.NewInstance = new ChatInstance();
                C.NewMessage = new ChatMessage();

             
                return View("Home", C);
            }
            else
            {
                ModelState.AddModelError("", "Invalid user name or password");
            }
            return View(new Person());
        }














        // Chat Functions

        public ActionResult CreateChat(int pid, int sh, int fid, string fname)
        {

            Person somePerson = db.People.Where(p => (p.Id == pid)).FirstOrDefault();

            // Setup All Classes
            AllClasses C = new AllClasses();
            C.User = somePerson;
            C.CurrentPage = sh;

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<Friend> F = db.Friends.Where(b => b.Id>0).ToList();
            C.FriendList = F;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;


            bool success = false;
            foreach (ChatInstance I in db.Instances)
            {
                if ((I.User1ID == pid && I.User2ID == fid) || (I.User2ID == pid && I.User1ID == fid)) 
                {
                    // Instance already exists
                    success = true;
                    I.IsActive = true;
                }
            }

            if(success == false)
            {
                // Create New Instance
                ChatInstance NewInstance = new ChatInstance();
                NewInstance.User1ID = somePerson.Id;
                NewInstance.User2ID = fid;
                NewInstance.User1 = somePerson.Username;
                NewInstance.User2 = fname;
                NewInstance.IsActive = true;
                db.Instances.Add(NewInstance);
            }

            
            db.SaveChanges();

            List<ChatInstance> CI = db.Instances
                   .Where(b => (b.User1ID == somePerson.Id) || (b.User2ID == somePerson.Id))
                   .ToList();
            C.InstanceList = CI;

            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();
            return View("Home", C);
        }


        public ActionResult CloseChatInstance(int pid, int sh, int Iid)
        {

            Person somePerson = db.People.Where(p => (p.Id == pid)).FirstOrDefault();

            // Setup All Classes
            AllClasses C = new AllClasses();
            C.User = somePerson;
            C.CurrentPage = sh;

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<Friend> F = db.Friends.Where(b => b.Id > 0).ToList();
            C.FriendList = F;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;



            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();


            // Set Instance to inactive
            ChatInstance Cinst = db.Instances.Where(p => (p.Id == Iid)).FirstOrDefault();
            Cinst.IsActive = false;
            db.SaveChanges();

            // Reload Instances
            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == somePerson.Id) || (b.User2ID == somePerson.Id)).ToList();
            C.InstanceList = CI;

            return View("Home", C);

        }


        public ActionResult MoveTo(int pid, int fid)
        {

            Person User = db.People.Where(p => (p.Id == pid)).FirstOrDefault();

            // Setup All Classes
            AllClasses C = new AllClasses();
            C.User = User;
            C.CurrentPage = fid;

            List<Person> U = db.People.Where(b => b.Id > 0).ToList();
            C.UserList = U;

            List<Blog> blgs = db.Blogs.Where(b => b.Id > 0).ToList();
            C.BlogList = blgs;

            List<Comment> coms = db.Comments.Where(b => b.Id > 0).ToList();
            C.CommentList = coms;

            List<Friend> F = db.Friends.Where(b => b.Id > 0).ToList();
            C.FriendList = F;

            List<ChatMessage> CM = db.Messages.Where(b => b.Id > 0).ToList();
            C.MessageList = CM;

            List<ChatInstance> CI = db.Instances.Where(b => (b.User1ID == User.Id) || (b.User2ID == User.Id)).ToList();
            C.InstanceList = CI;

            C.NewBlog = new Blog();
            C.NewComment = new Comment();
            C.NewInstance = new ChatInstance();
            C.NewMessage = new ChatMessage();


            return View("Home", C);

        }




        [HttpPost]
        public ActionResult AcceptFriendRequest()
        {

            LinkedList<Friend> msg = new LinkedList<Friend>();
            var success = false;


            foreach (Friend f in db.Friends)
            {
                if (f.Id == Convert.ToInt32(Request.Form[0]))
                {
                    f.Confirmed = true;
                    success = true;
                    msg.AddLast(f);
                }
            }

            if (success == true)
            {
                db.SaveChanges();
            }


            return Json(msg, JsonRequestBehavior.AllowGet);
        }
        
        [HttpPost]
        public ActionResult GetFriends()
        {
            LinkedList<Friend> msg = new LinkedList<Friend>();


            foreach (Friend f in db.Friends)
            {

                if ((f.Confirmed == true && f.FriendID == System.Convert.ToInt32(Request.Form[0])) || (f.Confirmed == true && f.UserID == System.Convert.ToInt32(Request.Form[0])))
                {
                    msg.AddLast(f);
                }
            }



            /* = db.ChatMessages
         .Where(b => b.Id > 0)
         .ToList();*/

            return Json(msg, JsonRequestBehavior.AllowGet);
        }

        [HttpPost]
        public ActionResult GetFriendRequest()
        {
            LinkedList<Friend> msg = new LinkedList<Friend>();


            foreach (Friend f in db.Friends )
            {

                if ((f.Confirmed == false && f.FriendID == System.Convert.ToInt32(Request.Form[0])) || (f.Confirmed == false && f.UserID == System.Convert.ToInt32(Request.Form[0])))
                {
                    msg.AddLast(f);
                }
            }



            /* = db.ChatMessages
         .Where(b => b.Id > 0)
         .ToList();*/

            return Json(msg, JsonRequestBehavior.AllowGet);
        }

        [HttpPost]
        public ActionResult SendMessageTest()
        {
            string x = Request.Form[0];
            string[] vals = x.Split(';');
            int ID = Convert.ToInt32(vals[1]);
            Person Author = db.People.Where(p => (p.Id == ID)).FirstOrDefault();

            ChatMessage NewMessage = new ChatMessage();
            NewMessage.InstanceId = Convert.ToInt32(vals[0]);
            NewMessage.Text = vals[2];
            NewMessage.AuthorId = Convert.ToInt32(vals[1]);
            NewMessage.AuthorUsername = Author.Username;
            NewMessage.Date = DateTime.Now.ToString();
            db.Messages.Add(NewMessage);
            db.SaveChanges();

            LinkedList<ChatMessage> msg = new LinkedList<ChatMessage>();
            return Json(msg, JsonRequestBehavior.AllowGet);
        }

        [HttpPost]
        public ActionResult AddFriendTest()
        {
            bool success = false;
            string x = Request.Form[0];
            string[] vals = x.Split(';');
            int ID = Convert.ToInt32(vals[0]);
            string fname = vals[1];
            Person User = db.People.Where(p => (p.Id == ID)).FirstOrDefault();
            


            // Add Friend
            Person Friend = db.People.Where(p => (p.Username == fname)).FirstOrDefault();

            if (Friend != null && Friend.Username != User.Username) // Friend Found and NOT self targeting
            {
                Friend FriendInstance = db.Friends.Where(p => (p.UserID == Friend.Id && p.FriendID == User.Id) || (p.FriendID == Friend.Id && p.UserID == User.Id)).FirstOrDefault(); // Check to see if they're already friends
                if (FriendInstance == null)
                {
                    // Add Friend to the database
                    Friend NewFriend = new Friend();
                    NewFriend.UserID = User.Id;
                    NewFriend.FriendID = Friend.Id;
                    NewFriend.UserUsername = User.Username;
                    NewFriend.FriendUsername = Friend.Username;
                    NewFriend.Confirmed = false;
                    db.Friends.Add(NewFriend);
                    db.SaveChanges();
                    success = true;
                }
            }


            LinkedList<bool> msg = new LinkedList<bool>();
            msg.AddLast(success);
            return Json(msg, JsonRequestBehavior.AllowGet);
        }

        [HttpPost]
        public ActionResult GetMessages()
        {

            LinkedList<ChatMessage> msg = new LinkedList<ChatMessage>();

            
                foreach (ChatMessage m in db.Messages.ToList())
                {
                    
                        if (m.InstanceId == System.Convert.ToInt32(Request.Form[0]))
                        {
                            msg.AddLast(m);
                        }
             

                }
           
            

            /* = db.ChatMessages
         .Where(b => b.Id > 0)
         .ToList();*/

            return Json(msg, JsonRequestBehavior.AllowGet);

        }




    }
}