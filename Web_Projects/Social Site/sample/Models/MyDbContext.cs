using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace sample.Models
{
    /// <summary>
    /// In order to support automatic DB dropping whenever a change is detected, we have to create a class
    /// derived from DropCreateDatabaseIfModelChanges.  Code wise, it doesn't do very much.
    /// </summary>
    public class ContextModelChangeInitializer : DropCreateDatabaseIfModelChanges<MyDbContext>
    {
        protected override void Seed(MyDbContext context)
        {
            base.Seed(context);

            //on new DB create, add "Joe User" to the DB
            context.People.Add(new Person()
                {
                    Email = "Joe@user.com",
                    First = "Joe",
                    Last = "User",
                    Username = "JOE",
                    Password = "test",
                    Str = 1,
                    Vit = 1,
                    Int = 1
                });

            context.SaveChanges();
        }
    }

    public class MyDbContext : DbContext
    {

        private void init()
        {
            //calling this will tell EF to automatically delete the 
            //actual DB whenever a change is detected.  Very handy for debugging, but not so
            //much for production.
            Database.SetInitializer<MyDbContext>(new ContextModelChangeInitializer());
        }
        public MyDbContext()
        {
            init();
        }

        public MyDbContext(string nameOrConnectionString)
            : base(nameOrConnectionString)
        {
            init();
        }

        //Our DB will have one table, which will be based on the Person class.
        public DbSet<Blog> Blogs { get; set; }
        public DbSet<Person> People { get; set; }
        public DbSet<Comment> Comments { get; set; }
        public DbSet<ChatInstance> Instances { get; set; }
        public DbSet<ChatMessage> Messages { get; set; }
        public DbSet<Friend> Friends { get; set; }
    }
}