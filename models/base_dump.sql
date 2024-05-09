--
-- PostgreSQL database dump
--

-- Dumped from database version 15.2
-- Dumped by pg_dump version 15.2

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: user_role; Type: TYPE; Schema: public; Owner: postgres
--

CREATE TYPE public.user_role AS ENUM (
    'Client',
    'Worker',
    'Admin'
);


ALTER TYPE public.user_role OWNER TO postgres;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: machine_brands; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.machine_brands (
    id integer NOT NULL,
    name text NOT NULL
);


ALTER TABLE public.machine_brands OWNER TO postgres;

--
-- Name: machine_brands_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.machine_brands_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.machine_brands_id_seq OWNER TO postgres;

--
-- Name: machine_brands_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.machine_brands_id_seq OWNED BY public.machine_brands.id;


--
-- Name: machine_marks; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.machine_marks (
    id integer NOT NULL,
    type integer NOT NULL,
    brand integer NOT NULL
);


ALTER TABLE public.machine_marks OWNER TO postgres;

--
-- Name: machine_marks_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.machine_marks_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.machine_marks_id_seq OWNER TO postgres;

--
-- Name: machine_marks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.machine_marks_id_seq OWNED BY public.machine_marks.id;


--
-- Name: machine_types; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.machine_types (
    id integer NOT NULL,
    name text NOT NULL
);


ALTER TABLE public.machine_types OWNER TO postgres;

--
-- Name: machine_types_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.machine_types_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.machine_types_id_seq OWNER TO postgres;

--
-- Name: machine_types_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.machine_types_id_seq OWNED BY public.machine_types.id;


--
-- Name: machines; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.machines (
    id integer NOT NULL,
    name text NOT NULL,
    owner integer NOT NULL,
    mark integer NOT NULL
);


ALTER TABLE public.machines OWNER TO postgres;

--
-- Name: machines_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.machines_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.machines_id_seq OWNER TO postgres;

--
-- Name: machines_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.machines_id_seq OWNED BY public.machines.id;


--
-- Name: orders; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.orders (
    id integer NOT NULL,
    date_start date DEFAULT CURRENT_DATE NOT NULL,
    date_end date,
    complete boolean DEFAULT false,
    description text,
    customer integer NOT NULL,
    executor integer,
    machine integer NOT NULL,
    service integer NOT NULL
);


ALTER TABLE public.orders OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.orders_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.orders_id_seq OWNER TO postgres;

--
-- Name: orders_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.orders_id_seq OWNED BY public.orders.id;


--
-- Name: services; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.services (
    id integer NOT NULL,
    name text NOT NULL,
    duration_months smallint DEFAULT 0 NOT NULL,
    duration_days smallint DEFAULT 0 NOT NULL,
    duration_hours smallint DEFAULT 0 NOT NULL,
    duration_minutes smallint DEFAULT 0 NOT NULL,
    price numeric(9,2) NOT NULL
);


ALTER TABLE public.services OWNER TO postgres;

--
-- Name: services_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.services_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.services_id_seq OWNER TO postgres;

--
-- Name: services_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.services_id_seq OWNED BY public.services.id;


--
-- Name: services_marks; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.services_marks (
    id integer NOT NULL,
    service integer NOT NULL,
    mark integer NOT NULL,
    duration_months smallint,
    duration_days smallint,
    duration_hours smallint,
    duration_minutes smallint,
    price numeric(9,2)
);


ALTER TABLE public.services_marks OWNER TO postgres;

--
-- Name: services_marks_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.services_marks_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.services_marks_id_seq OWNER TO postgres;

--
-- Name: services_marks_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.services_marks_id_seq OWNED BY public.services_marks.id;


--
-- Name: users; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.users (
    id integer NOT NULL,
    name text NOT NULL,
    login text NOT NULL,
    password text NOT NULL,
    role public.user_role NOT NULL
);


ALTER TABLE public.users OWNER TO postgres;

--
-- Name: users_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public.users_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.users_id_seq OWNER TO postgres;

--
-- Name: users_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public.users_id_seq OWNED BY public.users.id;


--
-- Name: machine_brands id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_brands ALTER COLUMN id SET DEFAULT nextval('public.machine_brands_id_seq'::regclass);


--
-- Name: machine_marks id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_marks ALTER COLUMN id SET DEFAULT nextval('public.machine_marks_id_seq'::regclass);


--
-- Name: machine_types id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_types ALTER COLUMN id SET DEFAULT nextval('public.machine_types_id_seq'::regclass);


--
-- Name: machines id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machines ALTER COLUMN id SET DEFAULT nextval('public.machines_id_seq'::regclass);


--
-- Name: orders id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders ALTER COLUMN id SET DEFAULT nextval('public.orders_id_seq'::regclass);


--
-- Name: services id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services ALTER COLUMN id SET DEFAULT nextval('public.services_id_seq'::regclass);


--
-- Name: services_marks id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services_marks ALTER COLUMN id SET DEFAULT nextval('public.services_marks_id_seq'::regclass);


--
-- Name: users id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users ALTER COLUMN id SET DEFAULT nextval('public.users_id_seq'::regclass);


--
-- Data for Name: machine_brands; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.machine_brands (id, name) FROM stdin;
1	First brand
2	Second brand
\.


--
-- Data for Name: machine_marks; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.machine_marks (id, type, brand) FROM stdin;
1	1	1
2	1	2
3	2	1
4	2	2
\.


--
-- Data for Name: machine_types; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.machine_types (id, name) FROM stdin;
1	First type
2	Second type
\.


--
-- Data for Name: machines; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.machines (id, name, owner, mark) FROM stdin;
11	first_first	2	1
12	first_second	2	2
13	second_first	2	3
15	second_second	2	4
\.


--
-- Data for Name: orders; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.orders (id, date_start, date_end, complete, description, customer, executor, machine, service) FROM stdin;
1	2024-05-07	\N	f	\N	2	\N	12	1
6	2024-05-07	\N	f	\N	2	\N	13	1
7	2024-05-07	2024-05-08	t	Все починил, сказали спасибо!	2	117	15	1
4	2024-05-03	\N	f	\N	2	117	11	1
\.


--
-- Data for Name: services; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.services (id, name, duration_months, duration_days, duration_hours, duration_minutes, price) FROM stdin;
1	Диагностика	0	2	12	0	2000.00
\.


--
-- Data for Name: services_marks; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.services_marks (id, service, mark, duration_months, duration_days, duration_hours, duration_minutes, price) FROM stdin;
1	1	1	\N	\N	\N	\N	4000.00
3	1	2	1	2	3	4	5000.00
4	1	3	5	4	3	\N	\N
5	1	4	\N	4	\N	20	500.00
\.


--
-- Data for Name: users; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.users (id, name, login, password, role) FROM stdin;
115	Евгений	admin	LG{5."s�'ߐ'/�̕;>?���z�6�~N\vF	Admin
117	Евгений	worker	LG{5."s�'ߐ'/�̕;>?���z�6�~N\vF	Worker
2	Евгений	client	LG{5."s�'ߐ'/�̕;>?���z�6�~N\vF	Client
\.


--
-- Name: machine_brands_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.machine_brands_id_seq', 2, true);


--
-- Name: machine_marks_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.machine_marks_id_seq', 5, true);


--
-- Name: machine_types_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.machine_types_id_seq', 2, true);


--
-- Name: machines_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.machines_id_seq', 15, true);


--
-- Name: orders_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.orders_id_seq', 8, true);


--
-- Name: services_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.services_id_seq', 1, true);


--
-- Name: services_marks_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.services_marks_id_seq', 5, true);


--
-- Name: users_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public.users_id_seq', 368, true);


--
-- Name: machine_brands machine_brands_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_brands
    ADD CONSTRAINT machine_brands_name_key UNIQUE (name);


--
-- Name: machine_brands machine_brands_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_brands
    ADD CONSTRAINT machine_brands_pkey PRIMARY KEY (id);


--
-- Name: machine_marks machine_marks_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_marks
    ADD CONSTRAINT machine_marks_pkey PRIMARY KEY (id);


--
-- Name: machine_marks machine_marks_type_brand_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_marks
    ADD CONSTRAINT machine_marks_type_brand_key UNIQUE (type, brand);


--
-- Name: machine_types machine_types_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_types
    ADD CONSTRAINT machine_types_name_key UNIQUE (name);


--
-- Name: machine_types machine_types_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_types
    ADD CONSTRAINT machine_types_pkey PRIMARY KEY (id);


--
-- Name: machines machines_owner_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machines
    ADD CONSTRAINT machines_owner_name_key UNIQUE (owner, name);


--
-- Name: machines machines_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machines
    ADD CONSTRAINT machines_pkey PRIMARY KEY (id);


--
-- Name: orders orders_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_pkey PRIMARY KEY (id);


--
-- Name: services_marks services_marks_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services_marks
    ADD CONSTRAINT services_marks_pkey PRIMARY KEY (id);


--
-- Name: services_marks services_marks_service_mark_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services_marks
    ADD CONSTRAINT services_marks_service_mark_key UNIQUE (service, mark);


--
-- Name: services services_name_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_name_key UNIQUE (name);


--
-- Name: services services_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services
    ADD CONSTRAINT services_pkey PRIMARY KEY (id);


--
-- Name: users users_login_key; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_login_key UNIQUE (login);


--
-- Name: users users_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.users
    ADD CONSTRAINT users_pkey PRIMARY KEY (id);


--
-- Name: orders_unique_index; Type: INDEX; Schema: public; Owner: postgres
--

CREATE UNIQUE INDEX orders_unique_index ON public.orders USING btree (customer, machine, service) WHERE (complete = false);


--
-- Name: machine_marks machine_marks_brand_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_marks
    ADD CONSTRAINT machine_marks_brand_fkey FOREIGN KEY (brand) REFERENCES public.machine_brands(id);


--
-- Name: machine_marks machine_marks_type_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machine_marks
    ADD CONSTRAINT machine_marks_type_fkey FOREIGN KEY (type) REFERENCES public.machine_types(id);


--
-- Name: machines machines_mark_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machines
    ADD CONSTRAINT machines_mark_fkey FOREIGN KEY (mark) REFERENCES public.machine_marks(id);


--
-- Name: machines machines_owner_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.machines
    ADD CONSTRAINT machines_owner_fkey FOREIGN KEY (owner) REFERENCES public.users(id);


--
-- Name: orders orders_customer_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_customer_fkey FOREIGN KEY (customer) REFERENCES public.users(id);


--
-- Name: orders orders_executor_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_executor_fkey FOREIGN KEY (executor) REFERENCES public.users(id);


--
-- Name: orders orders_machine_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_machine_fkey FOREIGN KEY (machine) REFERENCES public.machines(id);


--
-- Name: orders orders_service_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.orders
    ADD CONSTRAINT orders_service_fkey FOREIGN KEY (service) REFERENCES public.services(id);


--
-- Name: services_marks services_marks_mark_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services_marks
    ADD CONSTRAINT services_marks_mark_fkey FOREIGN KEY (mark) REFERENCES public.machine_marks(id);


--
-- Name: services_marks services_marks_service_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.services_marks
    ADD CONSTRAINT services_marks_service_fkey FOREIGN KEY (service) REFERENCES public.services(id);


--
-- PostgreSQL database dump complete
--

