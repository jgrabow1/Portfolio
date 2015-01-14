using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace sample.Models
{
    public class AllClasses
    {

        public Person User { get; set; }
        public List<Person> UserList { get; set; }
        public List<ChatInstance> InstanceList { get; set; }
        public List<ChatMessage> MessageList { get; set; }
        public List<Blog> BlogList { get; set; }
        public List<Friend> FriendList { get; set; }
        public List<Comment> CommentList { get; set; }
        public Blog NewBlog { get; set; }
        public Comment NewComment { get; set; }
        public ChatInstance NewInstance { get; set; }
        public ChatMessage NewMessage { get; set; }
        public int CurrentPage { get; set; }
        public Person UserSearch { get; set; }
        

    }

}